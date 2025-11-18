#pragma once

#include <vector>
#include <memory>
#include "Constants.h"

class Enemy;

class EnemySpawner
{
	public:

	EnemySpawner();

	void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& m_enemies);


	private:

	float m_enemySpawnInterval = EnemyInitSpawnInterval;
	float m_enemySpeedAddition = 0.0f;
	int m_enemyCount = 0;
	sf::Clock m_spawnClock;

};