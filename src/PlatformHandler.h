#pragma once

#include <vector>
#include "Platform.h"
#include "Constants.h"

class Game;
class Player;

class PlatformHandler
{
	public:

	void draw(sf::RenderTarget& target);
	void update(float dt, Player* player);
	void checkPlayerCollision(Player* player);
	std::vector<Platform>& getPlatformVec() { return m_platformVec; };

	private:

	void resolvePlayerCollison(int platformIdx, Player* player);
	void spawnPlatform();
	bool isPlatformOOB(Platform& platform);

	std::vector<Platform> m_platformVec;

	sf::Clock m_spawnClock;
	float m_spawnTime = PlatformInitSpawnTime;

	std::pair<float, float> m_platformLengthLimits{100.f, 300.f};
	std::pair<float, float> m_platformHeightLimits{200.f, GroundLevel - 100.f};
	
};