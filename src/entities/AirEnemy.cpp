#include "AirEnemy.h"
#include "utils.h"

AirEnemy::AirEnemy() : Enemy(300.f, eEnemyType::AIR)
{
	float enemyY = randomFloat(m_heightBoundaries.first, m_heightBoundaries.second);

	m_position.x = ScreenWidth;
	m_position.y = enemyY;
}

AirEnemy::AirEnemy(float speed) : Enemy(speed, eEnemyType::AIR)
{
	float enemyY = randomFloat(m_heightBoundaries.first, m_heightBoundaries.second);

	m_position.x = ScreenWidth;
	m_position.y = enemyY;
}
