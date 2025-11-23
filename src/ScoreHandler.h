#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

class ScoreHandler
{
	public:

	ScoreHandler(GameData& gameData);

	void addScore(int score) { m_gameData.playerScore += score; };
	int getScore() { return m_gameData.playerScore; };

	void update();

	private:

	GameData& m_gameData;
	sf::Clock m_scoreClock;
};