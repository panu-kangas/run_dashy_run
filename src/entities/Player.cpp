#include "Player.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <cmath>

#include <iostream>

Player::Player()
{
}

bool Player::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("player.png");
    if (pTexture == nullptr)
	{
        return false;
	}

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
	{
        return false;
	}

	m_prevPos = m_position;
    m_rotation = sf::degrees(0);
    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
	m_pSprite->setScale(sf::Vector2f(3.0f, 3.0f));
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
	m_playerNormalColor = m_pSprite->getColor();
    m_collisionRadius = collisionRadius;

	m_playerOutlines.setRadius(localBounds.size.x + 11.f);
	m_playerOutlines.setFillColor(sf::Color::White);
	m_playerOutlines.setPosition(m_position);
	sf::FloatRect outlineLocalBounds = m_playerOutlines.getLocalBounds();
	m_playerOutlines.setOrigin({outlineLocalBounds.size.x / 2.0f, outlineLocalBounds.size.y / 2.0f});

	m_jumpLoadBar.setSize({0, 10});
	m_jumpLoadBar.setFillColor(sf::Color::Red);
	m_jumpLoadBar.setPosition({m_position.x - TurboJumpBarLength / 2, m_position.y - localBounds.size.y - m_jumpLoadBar.getSize().y - 15.f});

    return true;
}

void Player::resetDash()
{
	m_canDash = true;
	m_outlineActive = true;
}

void Player::checkOutOfBounds()
{
	sf::FloatRect localBounds = m_pSprite->getLocalBounds();
	float leftLimit = 0.0f + localBounds.size.x;
	float rightLimit = ScreenWidth - localBounds.size.x;

	if (m_position.x < leftLimit)
		m_position.x = leftLimit;
	else if (m_position.x > rightLimit)
		m_position.x = rightLimit;
}

void Player::onPlatformCollision()
{
	m_isInAir = true;
	m_didDoubleJump = false;
	m_meteorAttack = false;
	m_isTurboJumping = false;
	m_velocity.x = 0;
	m_velocity.y = 0;
	m_isDashing = false;
	if (!m_isDashing)
		m_pSprite->setColor(m_playerNormalColor);
}

void Player::setOnPlatform(float posY, int platformIdx)
{
	if (m_meteorAttack)
		m_cameraShake = true;
	m_isInAir = false;
	m_didDoubleJump = false;
	m_meteorAttack = false;
	m_isTurboJumping = false;
	m_isOnPlatform = true;
	m_curPlatformIdx = platformIdx;
	m_position.y = posY;
	if (!m_isDashing)
		m_pSprite->setColor(m_playerNormalColor);
}

void Player::removeFromPlatform()
{
	m_isOnPlatform = false;
	m_curPlatformIdx = -1;
	m_isInAir = true;
}


void Player::checkGrounded()
{
	if (!m_isInAir || m_fallsThroughGround)
		return ;

	if (m_position.y >= GroundLevel)
	{	
		if (m_meteorAttack)
		{
			m_cameraShake = true;
		}

        m_isInAir = false;
		m_didDoubleJump = false;
		m_meteorAttack = false;
		m_sHold = false;
		m_velocity.y = 0;
		m_position.y = GroundLevel;
		if (!m_isDashing)
			m_pSprite->setColor(m_playerNormalColor);
	}
}

void Player::applyGravity(float dt)
{
	if (m_isTurboJumping || m_isDashing)
		return ;

	if (m_isInAir || m_fallsThroughGround)
	{
		if (m_velocity.y < 0)
			m_velocity.y += Gravity * 2.3 * dt;
		else
			m_velocity.y += Gravity * 3.3 * dt;
	}
	else
		m_velocity.y = 0;
}

void Player::handleSideMovement(bool aPressed, bool dPressed)
{
	if (m_meteorAttack || m_isDashing)
		return ;

	m_velocity.x = 0;

	if (aPressed && !dPressed && !m_isLoadingTurbo)
		m_velocity.x = -1 * m_speed;
	else if (dPressed && !aPressed && !m_isLoadingTurbo)
		m_velocity.x = m_speed;

	if (m_isOnPlatform)
	{
		m_velocity.x += PlatformSpeed;
	}

	if (m_velocity.x > 0)
		m_facingLeft = false;
	else if (m_velocity.x < 0)
		m_facingLeft = true;
}

void Player::checkDash(bool spacePressed)
{
	if (m_meteorAttack || m_isTurboJumping || !m_canDash)
		return ;

	if (spacePressed && !m_spaceHold)
	{
		m_spaceHold = true;
		m_isDashing = true;
		m_canDash = false;
		m_outlineActive = false;
		m_velocity.x = m_facingLeft ? -1 * DashSpeed : DashSpeed;
		m_velocity.y = 0;
		m_pSprite->setColor(PlayerDashColor);
		m_dashEffectClock.restart();
	}
}

void Player::checkMeteorAttack(bool sPressed)
{
	if (!m_isInAir || m_isDashing)
		return ;

	if (sPressed && !m_sHold)
	{
		m_meteorAttack = true;
		m_sHold = true;
		m_velocity.y = MeteorAttackSpeed;
		m_velocity.x = 0;
		m_pSprite->setColor(PlayerDashColor);
	}
}

void Player::checkTurboJump(bool sPressed)
{
	if (m_isInAir || m_meteorAttack || m_isDashing || m_isTurboJumping)
		return ;

	if (sPressed && !m_sHold)
	{
		m_sHold = true;
		m_isLoadingTurbo = true;
		m_velocity.x = 0;
		m_turboLoadClock.restart();
	}
}


void Player::checkJumps(bool wPressed)
{
	if (m_isTurboJumping || m_isLoadingTurbo || m_meteorAttack || m_isDashing)
		return ;

	if (wPressed && !m_wHold && !m_didDoubleJump && m_velocity.y > PlayerJumpPower + 400.f)
    {
		if (!m_isInAir)
		{
        	m_isInAir = true;
		}
		else
		{
			m_didDoubleJump = true;
		}

		m_wHold = true;
		m_velocity.y = PlayerJumpPower;
    }
}

void Player::handleInput()
{
	bool wPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W);
	checkJumps(wPressed);

	bool aPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
	bool dPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
	handleSideMovement(aPressed, dPressed);

	bool sPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S);
	checkTurboJump(sPressed);
	checkMeteorAttack(sPressed);

	bool spacePressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
	checkDash(spacePressed);


	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		m_wHold = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		m_spaceHold = false;
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		if (m_isLoadingTurbo)
			m_isLoadingTurbo = false;
		m_sHold = false;
	}
}

void Player::checkTimers()
{
	if (m_isLoadingTurbo && m_turboLoadClock.getElapsedTime().asSeconds() >= TurboJumpLoadTime)
	{
		m_isLoadingTurbo = false;
		m_isTurboJumping = true;
		m_velocity.y = TurboJumpPower;
		m_turboEffectClock.restart();
	}

	if (m_isTurboJumping && m_turboEffectClock.getElapsedTime().asSeconds() >= TurboJumpEffectTime)
	{
		m_isTurboJumping = false;
		m_isInAir = true;
	}

	if (m_isDashing && m_dashEffectClock.getElapsedTime().asSeconds() >= DashEffectTime)
	{
		m_isDashing = false;
		m_pSprite->setColor(m_playerNormalColor);
		m_dashCooldownClock.restart();
	}

	if (!m_isDashing && !m_canDash && m_dashCooldownClock.getElapsedTime().asSeconds() >= DashCooldown)
	{
		resetDash();
	}
}

void Player::update(float dt)
{
	m_prevPos = m_position;

	checkTimers();
	handleInput();
	applyGravity(dt);

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_playerOutlines.setPosition(m_position);

	
	checkOutOfBounds();
    checkGrounded();
	updateJumpLoadBar();
}

void Player::updateJumpLoadBar()
{
	if (!m_isLoadingTurbo)
	{
		if (m_jumpLoadBar.getSize().x > 0)
			m_jumpLoadBar.setSize({0, m_jumpLoadBar.getSize().y});
		if (m_jumpLoadBar.getFillColor() != sf::Color::Red)
			m_jumpLoadBar.setFillColor(sf::Color::Red);
		return;
	}
	
	float turboLoadCurTime = m_turboLoadClock.getElapsedTime().asSeconds();
	float barLength = (turboLoadCurTime / TurboJumpLoadTime) * TurboJumpBarLength;
	if (barLength >= TurboJumpBarLength)
	{
		barLength = TurboJumpBarLength;
		m_jumpLoadBar.setFillColor(sf::Color::Green);
	}
	m_jumpLoadBar.setSize({barLength, m_jumpLoadBar.getLocalBounds().size.y});
	sf::FloatRect playerBounds = m_pSprite->getLocalBounds();
	m_jumpLoadBar.setPosition({m_position.x - TurboJumpBarLength / 2, m_position.y - playerBounds.size.y - m_jumpLoadBar.getSize().y - 15.f});

}

void Player::render(sf::RenderTarget& target) const
{
    m_pSprite->setRotation(m_rotation);
    m_pSprite->setPosition(m_position);

	if (m_outlineActive)
		target.draw(m_playerOutlines);

    target.draw(*m_pSprite);
	target.draw(m_jumpLoadBar);

}


sf::Vector2f Player::getSize()
{
	if (!m_pSprite)
	{
		return {0, 0};
	}

	return m_pSprite->getLocalBounds().size;
}

sf::FloatRect Player::getGlobalBounds()
{
	if (!m_pSprite)
	{
		return sf::FloatRect(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(0.0f, 0.0f));
	}

	return m_pSprite->getGlobalBounds();
}

void Player::checkCameraShake(sf::RenderTarget& target)
{
	if (m_cameraShake)
	{
		if (handleCameraShake(target))
			m_cameraShake = false;
	}
}

bool Player::handleCameraShake(sf::RenderTarget& target)
{	
	if (m_shakeTimer.getElapsedTime().asSeconds() < m_shakeInterval)
		return false;

	sf::View view = target.getDefaultView();
	sf::Vector2f offset = m_shakeOffsets[m_shakeIdx];
	view.move(offset);
	target.setView(view);

	m_shakeIdx++;
	if (m_shakeIdx == m_shakeOffsets.size())
	{
		m_shakeIdx = 0;
		target.setView(target.getDefaultView());
		return true;
	}

	m_shakeTimer.restart();

	return false;
}

