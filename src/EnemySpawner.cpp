#include "EnemySpawner.h"
#include "entities/GroundEnemy.h"
#include "entities/AirEnemy.h"
#include "entities/ShootEnemy.h"
#include "utils.h"

#include <iostream>

EnemySpawner::EnemySpawner(GameData& gameData) : m_gameData(gameData)
{
}

void EnemySpawner::updateSpeedAndSpawnInterval()
{
	if (m_speedUpdateClock.getElapsedTime().asSeconds() > EnemySpeedUpdateInterval && m_enemySpawnInterval > EnemyMinSpawnInterval)
	{
		m_enemySpawnInterval -= 0.15f;
		if (m_enemySpawnInterval < EnemyMinSpawnInterval)
			m_enemySpawnInterval = EnemyMinSpawnInterval;

		if (m_enemySpeedAddition < EnemyMaxSpeedAddition)
			m_enemySpeedAddition += EnemySpeedAddition;

		if (m_shootInterval > 1.f)
			m_shootInterval -= 0.3f;

		m_speedUpdateClock.restart();
	}
}


void EnemySpawner::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& enemies, std::vector<std::unique_ptr<Projectile>>& projVec)
{
    if (m_spawnClock.getElapsedTime().asSeconds() < m_enemySpawnInterval)
		return ;

	std::unique_ptr<Enemy> pEnemy;
	eEnemyType spawnType;
	bool spawnOK = false;
	float rand = 0;

	while (!spawnOK)
	{
		rand = randomFloat(0.f, 100.f);

		if (m_enemyCount % 7 == 0 && m_gameData.playerScore > ShootEnemyScoreLimit)
		{
			pEnemy = std::make_unique<ShootEnemy>(ShootEnemyBaseSpeed + m_enemySpeedAddition, m_shootInterval, projVec);
			spawnType = SHOOT;
		}
		else if (rand < 40.f)
		{
			pEnemy = std::make_unique<AirEnemy>(AirEnemyBaseSpeed + m_enemySpeedAddition);
			spawnType = AIR;
		}
		else
		{
			pEnemy = std::make_unique<GroundEnemy>(GroundEnemyBaseSpeed + m_enemySpeedAddition);
			spawnType = GROUND;
		}

		if (spawnType == m_prevType && m_spawnStreakCount == 4)
			continue ;
		else
			spawnOK = true;
	}

	if (spawnType == m_prevType)
	{
		m_spawnStreakCount++;
	}
	else
	{
		m_spawnStreakCount = 0;
	}

	if (spawnType != SHOOT)
		m_prevType = spawnType;

	if (pEnemy->init())
		enemies.push_back(std::move(pEnemy));

	m_spawnClock.restart();
	updateSpeedAndSpawnInterval();
	
	m_enemyCount++;

}
