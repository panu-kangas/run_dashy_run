#include "CoinHandler.h"
#include "utils.h"
#include "entities/Player.h"
#include "ResourceManager.h"

#include <iostream>

CoinHandler::CoinHandler(GameData& gameData) : m_gameData(gameData)
{
	m_pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
	// Error handling...
}

void CoinHandler::spawnCoin()
{
	if (m_spawnClock.getElapsedTime().asSeconds() < m_spawnInterval)
		return ;


	float randomY = randomFloat(100, GroundLevel - 100);
	sf::Vector2f pos{ ScreenWidth, randomY };

	m_coinVec.push_back({pos, 1});

	m_spawnClock.restart();
}

void CoinHandler::checkPlayerCollision(Player* player)
{
	for (size_t i = 0; i < m_coinVec.size(); ++i)
	{
		float distance = (player->getPosition() - m_coinVec[i].getShape().getPosition()).lengthSquared();
		float minDistance = std::pow(player->getCollisionRadius() + m_coinVec[i].getShape().getRadius(), 2);
		if (distance < minDistance)
		{
			m_gameData.playerCoins += m_coinVec[i].getValue();
			std::swap(m_coinVec[i], m_coinVec.back());
			m_coinVec.pop_back();
		}
	}
}

void CoinHandler::update(float dt)
{
	spawnCoin();

	for (size_t i = 0; i < m_coinVec.size(); ++i)
	{
		m_coinVec[i].update(dt);

		// Check OOB
		if (m_coinVec[i].getShape().getPosition().x < 0)
		{
			std::swap(m_coinVec[i], m_coinVec.back());
			m_coinVec.pop_back();
			continue;
		}
	}

}

void CoinHandler::render(sf::RenderTarget& target)
{
	for (auto& coin : m_coinVec)
	{
		coin.render(target);
	}

	sf::String text = "Coins: " + std::to_string(m_gameData.playerCoins);
	sf::Text coinInfoText(*m_pFont, text);

	coinInfoText.setCharacterSize(25);
	coinInfoText.setFillColor(sf::Color::Yellow);
	coinInfoText.setPosition({ScreenWidth - coinInfoText.getGlobalBounds().size.x - 25, 25});

	target.draw(coinInfoText);

}
