#pragma once

#include "Enemy.h"
#include "Constants.h"


class AirEnemy : public Enemy
{

public:

	AirEnemy();
	AirEnemy(float speed);

private:

	std::pair<float, float> m_heightBoundaries{EnemyMinSpawnHeight, EnemyMaxSpawnHeight};

};