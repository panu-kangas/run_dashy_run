#include "EnemySpawner.h"
#include "entities/Enemy.h"
#include "entities/GroundEnemy.h"
#include "entities/AirEnemy.h"
#include "utils.h"

EnemySpawner::EnemySpawner()
{
}

void EnemySpawner::spawnEnemy(std::vector<std::unique_ptr<Enemy>>& m_enemies)
{
    if (m_spawnClock.getElapsedTime().asSeconds() >= m_enemySpawnInterval)
    {
		std::unique_ptr<Enemy> pEnemy;

		float rand = randomFloat(0.f, 100.f);

		if (rand < 30.f)
			pEnemy = std::make_unique<GroundEnemy>(GroundEnemyBaseSpeed + m_enemySpeedAddition);
		else
			pEnemy = std::make_unique<AirEnemy>(AirEnemyBaseSpeed + m_enemySpeedAddition);

        if (pEnemy->init())
            m_enemies.push_back(std::move(pEnemy));

		m_enemyCount++;
		m_spawnClock.restart();

		if (m_enemyCount % EnemySpawnUpdateLimit == 0 && m_enemySpawnInterval > EnemyMinSpawnInterval)
		{
			m_enemySpawnInterval -= 0.2f;
			if (m_enemySpawnInterval < EnemyMinSpawnInterval)
				m_enemySpawnInterval = EnemyMinSpawnInterval;

			if (m_enemySpeedAddition < EnemyMaxSpeedAddition)
				m_enemySpeedAddition += EnemySpeedAddition;
		}
	}

}
