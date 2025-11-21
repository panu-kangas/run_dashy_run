#pragma once

#include "Enemy.h"
#include "Projectile.h"


class ShootEnemy : public Enemy
{

public:

	ShootEnemy() = delete;
	ShootEnemy(float speed);

    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	void shoot();
	bool isProjOOB(Projectile* proj);

	std::vector<std::unique_ptr<Projectile>> m_projVec;

	bool m_isShooting = false;
	bool m_hasShot = false;

	sf::Clock m_shootStartClock;
	sf::Clock m_shootEffectClock;

};