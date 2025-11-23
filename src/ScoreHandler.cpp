#include "ScoreHandler.h"

ScoreHandler::ScoreHandler(GameData& gameData) : m_gameData(gameData)
{
}

void ScoreHandler::update()
{
	if (m_scoreClock.getElapsedTime().asSeconds() < ScoreInterval)
		return ;

	m_gameData.playerScore += 1;
	m_scoreClock.restart();
}