#include "ScoreHandler.h"
#include "Constants.h"

void ScoreHandler::update()
{
	if (m_scoreClock.getElapsedTime().asSeconds() < ScoreInterval)
		return ;

	m_score += 1;
	m_scoreClock.restart();
}