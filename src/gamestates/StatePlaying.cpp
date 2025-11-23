#include "StatePlaying.h"
#include "StatePaused.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "utils.h"
#include <memory>
#include <iostream>
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

StatePlaying::StatePlaying(StateStack& stateStack, GameData& gameData)
    : m_stateStack(stateStack), m_gameData(gameData)
{
	m_gameData.playerScore = 0;
}

bool StatePlaying::init()
{
	const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("spike.png");
	if (pTexture == nullptr)
	{
        return false;
	}
    m_spikeSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_spikeSprite)
	{
        return false;
	}
	m_spikeSprite->setScale({2.0f, 2.0f});

	m_pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
    if (m_pFont == nullptr)
        return false;

    m_ground.setSize({ScreenWidth, 256.0f});
    m_ground.setPosition({0.0f, GroundLevel});
    m_ground.setFillColor(GroundColor);

    m_pPlayer = std::make_unique<Player>();
    if (!m_pPlayer || !m_pPlayer->init())
        return false;
    m_pPlayer->setPosition(sf::Vector2f(200, GroundLevel));

	m_pEnemySpawner = std::make_unique<EnemySpawner>(m_gameData);
	if (!m_pEnemySpawner)
		return false;

	m_pScoreHandler = std::make_unique<ScoreHandler>(m_gameData);
	if (!m_pScoreHandler)
		return false;

	m_pPlatformHandler = std::make_unique<PlatformHandler>(m_gameData);
	if (!m_pPlatformHandler)
		return false;

    return true;
}

void StatePlaying::checkEnemyCollisionAndOOB()
{
	if (m_enemies.empty())
		return ;

    bool playerDied = false;
	float leftBoundary = 0.0f - m_enemies[0]->getCollisionRadius();
	size_t i = 0;
    while (i < m_enemies.size())
    {
		if (m_enemies[i]->getPosition().x <= leftBoundary)
		{
			std::swap(m_enemies[i], m_enemies.back());
			m_enemies.pop_back();
			continue;
		}

        float distance = (m_pPlayer->getPosition() - m_enemies[i]->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + m_enemies[i]->getCollisionRadius(), 2.0f);

        if (distance <= minDistance)
        {
			if (m_pPlayer->isDashing())
			{
				std::swap(m_enemies[i], m_enemies.back());
				m_enemies.pop_back();
				m_pPlayer->resetDash();
				m_pScoreHandler->addScore(10);
				continue;
			}
			else
			{
				playerDied = true;
				break;
			}
        }
		i++;
    }

    if (playerDied)
	{
		m_hasEnded = true;

	}
}

bool StatePlaying::isProjOOB(Projectile* proj)
{
	sf::FloatRect bounds = proj->getShape().getGlobalBounds();

	if (bounds.position.x < 0 || bounds.position.x + bounds.size.x > ScreenWidth)
		return true;
	else if (bounds.position.y < 0 || bounds.position.y + bounds.size.y > GroundLevel)
		return true;

	return false;
}

void StatePlaying::handleGroundBlinking()
{
	if (!m_isGroundBlinking)
		return ;

	if (m_groundBlinkClock.getElapsedTime().asSeconds() > m_prevBlink + GroundBlinkInterval)
	{
		m_isGroundVisible = !m_isGroundVisible;
		m_prevBlink = m_groundBlinkClock.getElapsedTime().asSeconds();
	}

	if (m_groundBlinkClock.getElapsedTime().asSeconds() > GroundBlinkEffectTime)
	{
		m_isGroundVisible = false;
		m_pPlayer->setWorldHasGround(false);
		m_isGroundBlinking = false;
		m_prevBlink = 0.0f;
		m_groundDissappearClock.start();
	}
}

void StatePlaying::handleGroundDissappear()
{
	if (m_pScoreHandler->getScore() < GroundVanishScoreLimit)
		return ;

	if (m_hasGround && m_groundDissappearClock.getElapsedTime().asSeconds() >= GroundDissappearInterval)
	{
		m_hasGround = false;
		m_isGroundBlinking = true;
		m_groundBlinkClock.restart();
		m_groundDissappearClock.restart();
		m_groundDissappearClock.stop();
	}
	else if (!m_hasGround && m_groundDissappearClock.getElapsedTime().asSeconds() >= GroundReturnTime)
	{
		m_hasGround = true;
		m_isGroundVisible = true;
		m_pPlayer->setWorldHasGround(true);
		m_groundDissappearClock.restart();
	}
	handleGroundBlinking();
}

void StatePlaying::updateEntities(float dt)
{
	// PLAYER
	m_pPlayer->update(dt);
	if (!m_pPlayer->isInAir() && !m_pPlayer->isOnPlatform() && !m_isGroundBlinking && !m_hasGround)
	{
		m_pPlayer->setFallsThroughGround(true);
	}

	// Player fell out of screen
	if (m_pPlayer->getPosition().y > ScreenHeight)
	{
		m_hasEnded = true;
	}

	// Player hit Spike wall
	float playerLeft = m_pPlayer->getPosition().x - m_pPlayer->getCollisionRadius();
	if (playerLeft < m_spikeSprite->getLocalBounds().size.x * 2)
	{
		m_hasEnded = true;
	}

	// PLATFORM
	m_pPlatformHandler->update(dt, m_pPlayer.get());
	m_pPlatformHandler->checkPlayerCollision(m_pPlayer.get());

	// ENEMY
    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
    {
        pEnemy->update(dt);
    }

	// PROJECTILE
	sf::FloatRect playerBounds = m_pPlayer->getGlobalBounds();
	std::vector<Platform>& platformVec = m_pPlatformHandler->getPlatformVec();
	for (size_t i = 0; i < m_projVec.size(); ++i)
	{
		m_projVec[i]->update(dt);

		// Check Projectile collisions
		sf::FloatRect projBounds = m_projVec[i]->getShape().getGlobalBounds();
		if (checkRectCollision(playerBounds, projBounds))
		{
			float distance = (m_pPlayer->getPosition() - m_projVec[i]->getPosition()).lengthSquared();
			float minDistance = std::pow(m_pPlayer->getCollisionRadius() + m_projVec[i]->getShape().getSize().x, 2);
			if (distance < minDistance)
			{
				if (m_pPlayer->isDashing())
					m_projVec[i]->setIsDestroyed(true);
				else
					m_hasEnded = true;
			}
		}
		for (auto& platform : platformVec)
		{
			sf::FloatRect platformBounds = platform.getShape().getGlobalBounds();
			if (checkRectCollision(platformBounds, projBounds))
			{
				m_projVec[i]->setIsDestroyed(true);
			}
		}

		if (isProjOOB(m_projVec[i].get()) || m_projVec[i]->getIsDestroyed())
		{
			std::swap(m_projVec[i], m_projVec.back());
			m_projVec.pop_back();
			continue;
		}
	}

	checkEnemyCollisionAndOOB();
}

void StatePlaying::update(float dt)
{
	if (m_hasEnded)
	{
		bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P);
		if (pressed)
		{
			m_stateStack.popDeferred();
		}
		return ;
	}

	handleGroundDissappear();
	m_pScoreHandler->update();
	m_pEnemySpawner->spawnEnemy(m_enemies, m_projVec);

    bool isPauseKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_hasPauseKeyBeenReleased |= !isPauseKeyPressed;
    if (m_hasPauseKeyBeenReleased && isPauseKeyPressed)
    {
        m_hasPauseKeyBeenReleased = false;
        m_stateStack.push<StatePaused>();
    }

	updateEntities(dt);
}

void StatePlaying::renderEntities(sf::RenderTarget& target) const
{
	m_pPlatformHandler->draw(target);

	for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
    	pEnemy->render(target);
		
	m_pPlayer->checkCameraShake(target);
    m_pPlayer->render(target);

	for (auto& proj : m_projVec)
	{
		proj->render(target);
	}
}


void StatePlaying::render(sf::RenderTarget& target) const
{

	if (m_isGroundBlinking && !m_hasEnded)
	{
		drawHeaderText(m_pFont, target, "Watch out! The floor is about to vanish!");
	}

	if (m_isGroundVisible)
	{
		target.draw(m_ground);
	}

	renderEntities(target);

	drawSpikeWall(target);

	if (m_hasEnded)
	{
		drawHeaderText(m_pFont, target, "Dashy died! Your Final score:  " + std::to_string(m_pScoreHandler->getScore()));
		drawCenteredText(m_pFont, target, "Press P to play again");
	}
	else
	{
		drawCenteredText(m_pFont, target, "Your Score:  " + std::to_string(m_pScoreHandler->getScore()), -370.f);
	}
}

void StatePlaying::drawSpikeWall(sf::RenderTarget& target) const
{
	float y = 0;

	while (y < GroundLevel)
	{
		m_spikeSprite->setPosition({0, y});
		target.draw(*m_spikeSprite);
		y += m_spikeSprite->getLocalBounds().size.y * 2;
	}

	m_spikeSprite->setPosition({0, y});
	target.draw(*m_spikeSprite);
	y += m_spikeSprite->getLocalBounds().size.y * 2;
}


