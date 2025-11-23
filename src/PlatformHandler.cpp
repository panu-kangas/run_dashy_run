#include "PlatformHandler.h"
#include "entities/Player.h"
#include "utils.h"

#include <iostream>

PlatformHandler::PlatformHandler(GameData& gameData) : m_gameData(gameData)
{
}


void PlatformHandler::spawnPlatform()
{
//	float rand = randomFloat(0, 150);

	if (m_platformCount % m_wallSpawnInterval == 0 && m_gameData.playerScore > WallScoreLimit)
	{
		// Spawn a wall with a gap
		
		float gapStartY = randomFloat(60, GroundLevel - WallGap - 30);

		float platformY1 = 0;
		float platformSizeY1 = gapStartY;
	
		float platformY2 = platformSizeY1 + WallGap;
		float platformSizeY2 = ScreenHeight - platformY2;

		float platformX = ScreenWidth;
		float platformSizeX = WallThickness;
	
		m_platformVec.push_back(Platform({platformX, platformY1}, {platformSizeX, platformSizeY1}, PlatformSpeed));
		m_platformVec.push_back(Platform({platformX, platformY2}, {platformSizeX, platformSizeY2}, PlatformSpeed));
	}
	else
	{
		// Spawn a platform

		float platformX = ScreenWidth;
		float platformY = randomFloat(m_platformHeightLimits.first, m_platformHeightLimits.second);
		float platformSizeX = randomFloat(m_platformLengthLimits.first, m_platformLengthLimits.second);
		float platformSizeY = PlatformHeight;

		m_platformVec.push_back(Platform({platformX, platformY}, {platformSizeX, platformSizeY}, PlatformSpeed));
	}

	m_platformCount++;

}

bool PlatformHandler::isPlatformOOB(Platform& platform)
{
	sf::FloatRect bounds = platform.getShape().getGlobalBounds();

	if (bounds.position.x + bounds.size.x < 0)
		return true;

	return false;
}


void PlatformHandler::update(float dt, Player* player)
{
	size_t i = 0;
	while (i < m_platformVec.size())
	{
		m_platformVec[i].update(dt);
		if (isPlatformOOB(m_platformVec[i]))
		{
			std::swap(m_platformVec[i], m_platformVec.back());
			m_platformVec.pop_back();
			continue;
		}
	
		if (m_platformVec[i].checkHasPlayer() && m_platformVec[i].isPlayerOOB(player))
		{
			player->removeFromPlatform();
			m_platformVec[i].setHasPlayer(false);
		}

		i++;
	}

	if (m_spawnClock.getElapsedTime().asSeconds() < m_spawnTime)
		return ;

	spawnPlatform();
	m_spawnClock.restart();
	
}


void PlatformHandler::draw(sf::RenderTarget& target)
{
	for (auto& platform : m_platformVec)
	{
		platform.draw(target);
	}
}

void PlatformHandler::resolvePlayerCollison(int idx, Player* player)
{
	sf::FloatRect prevPlayerGlobalBounds = player->getPrevGlobalBounds();
	float playerPrevBottom = prevPlayerGlobalBounds.position.y + prevPlayerGlobalBounds.size.y;
	float playerPrevTop = prevPlayerGlobalBounds.position.y;
	float playerPrevRight = prevPlayerGlobalBounds.position.x + prevPlayerGlobalBounds.size.x;
	float playerPrevLeft = prevPlayerGlobalBounds.position.x;


	sf::FloatRect platformBounds = m_platformVec[idx].getShape().getGlobalBounds();
	float platformTop = platformBounds.position.y;
	float platformBottom = platformBounds.position.y + platformBounds.size.y;
	float platformLeft = platformBounds.position.x;
	float platformRight = platformBounds.position.x + platformBounds.size.x;

/*	std::cout << "*** COLLISION INFO ***\n"
//	<< "Player curPos: x: " << player->getCurPosition().x << ", y: " << player->getCurPosition().y << "\n"
	<< "Player cur bottom based on global bounds: " << player->getGlobalBounds().position.y + player->getGlobalBounds().size.y << "\n"

//	<< "Player prevPos: x: " << prevPos.x << ", y: " << prevPos.y << "\n"
//	<< "Player radius: " << playerRadius << "\n"
	<< "Player prev bottom: " << playerPrevBottom << "\n"
	<< "Platform Top: " << platformTop << "\n\n"; */

	if (playerPrevBottom < platformTop)
	{
		// std::cout << "Top collision, setting player on platform!\n";

		player->setOnPlatform(platformTop - prevPlayerGlobalBounds.size.y / 2 - 3.f, idx);
		m_platformVec[idx].setHasPlayer(true);
	}
	else if (playerPrevTop > platformBottom)
	{
		// std::cout << "Bottom collision!\n";

		sf::Vector2f newPosition{ player->getCurPosition().x, platformBottom + prevPlayerGlobalBounds.size.y / 2 + 3.f };
		sf::Vector2f newVelocity { player->getVelocity().x, 0 };
		player->onPlatformCollision(newPosition, newVelocity);
		player->setIsTurboJumping(false);
		player->setIsInAir(true);
	}
	else if (playerPrevRight < platformLeft)
	{
		// std::cout << "Left collision!\n";

		sf::Vector2f newPosition{ platformLeft - prevPlayerGlobalBounds.size.x / 2 - 10.f, player->getCurPosition().y };
		sf::Vector2f newVelocity { 0, player->getVelocity().y };
		player->onPlatformCollision(newPosition, newVelocity);
		player->setDashInactive();
	}
	else if (playerPrevLeft > platformRight)
	{
		// std::cout << "Right collision!\n";

		sf::Vector2f newPosition{ platformRight + prevPlayerGlobalBounds.size.x / 2 + 10.f, player->getCurPosition().y };
		sf::Vector2f newVelocity { 0, player->getVelocity().y };
		player->onPlatformCollision(newPosition, newVelocity);
		player->setDashInactive();
	}
	else
	{
		// Backup for failing detection

		float playerCenter = player->getCurPosition().x;

		if (playerCenter > platformRight)
		{
			sf::Vector2f newPosition{ platformRight + prevPlayerGlobalBounds.size.x / 2, player->getCurPosition().y };
			sf::Vector2f newVelocity { 0, player->getVelocity().y };
			player->onPlatformCollision(newPosition, newVelocity);
			player->setDashInactive();
		}
		else
		{
			sf::Vector2f newPosition{ platformLeft - prevPlayerGlobalBounds.size.x / 2, player->getCurPosition().y };
			sf::Vector2f newVelocity { 0, player->getVelocity().y };
			player->onPlatformCollision(newPosition, newVelocity);
			player->setDashInactive();
		}
	}
	
}

void PlatformHandler::checkPlayerCollision(Player* player)
{
	sf::FloatRect playerBounds = player->getGlobalBounds();

	for (size_t i = 0; i < m_platformVec.size(); ++i)
	{
		if (checkRectCollision(playerBounds, m_platformVec[i].getShape().getGlobalBounds()))
		{
			resolvePlayerCollison(i, player);
			return ;
		}
	}
}