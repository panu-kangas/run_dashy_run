#include "GroundEnemy.h"
#include "Constants.h"

GroundEnemy::GroundEnemy() : Enemy()
{
	m_position.x = ScreenWidth;
	m_position.y = GroundLevel;
}

GroundEnemy::GroundEnemy(float speed) : Enemy(speed, eEnemyType::GROUND)
{
	m_position.x = ScreenWidth;
	m_position.y = GroundLevel;
}
