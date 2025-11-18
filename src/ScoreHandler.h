#pragma once

#include <SFML/Graphics.hpp>

class ScoreHandler
{
	public:

	void addScore(int score) { m_score += score; };
	int getScore() { return m_score; };

	void update();

	private:

	int m_score = 0;
	sf::Clock m_scoreClock;
};