#pragma once

#include "Enemy.h"
#include "Projectile.h"


class ShootEnemy : public Enemy
{

public:

	ShootEnemy() = delete;
	ShootEnemy(float speed, float shootInterval, std::vector<std::unique_ptr<Projectile>>& projVec);

    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	void shoot();

	std::vector<std::unique_ptr<Projectile>>& m_projVec;

	bool m_isShooting = false;
	bool m_hasShot = false;

	sf::Clock m_shootStartClock;
	sf::Clock m_shootEffectClock;
	float m_shootInterval;

};