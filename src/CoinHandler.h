#pragma once

#include <SFML/System/Clock.hpp>
#include <vector>
#include "Coin.h"
#include "Constants.h"

class Player;

class CoinHandler
{

public:

	CoinHandler() = delete;
	CoinHandler(GameData& gameData);

	void update(float dt);
	void render(sf::RenderTarget& target);
	void checkPlayerCollision(Player* player);

	std::vector<Coin>& getCoinVec() { return m_coinVec; };

private:

	void spawnCoin();

	std::vector<Coin> m_coinVec;

	GameData& m_gameData;

	sf::Clock m_spawnClock;
	float m_spawnInterval = CoinInitSpawnInterval;

	const sf::Font* m_pFont;

};