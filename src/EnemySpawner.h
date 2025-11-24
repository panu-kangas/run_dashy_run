#pragma once

#include <vector>
#include <memory>
#include "Constants.h"
#include "entities/Enemy.h"
#include "entities/Projectile.h"

class EnemySpawner
{
	public:

	EnemySpawner(GameData& gameData);

	void spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Projectile>>& projVec);

	private:

	void updateSpeedAndSpawnInterval();

	GameData& m_gameData;

	float m_enemySpawnInterval = EnemyInitSpawnInterval;
	float m_enemySpeedAddition = 0.0f;
	float m_shootInterval = ShootEnemyShootInterval;

	int m_enemyCount = 0;
	int m_spawnStreakCount = 0;

	sf::Clock m_spawnClock;
	sf::Clock m_speedUpdateClock;

	eEnemyType m_prevType;

};