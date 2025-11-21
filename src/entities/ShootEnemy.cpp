#include "ShootEnemy.h"
#include "Constants.h"
#include "utils.h"

#include <iostream>

ShootEnemy::ShootEnemy(float speed) : Enemy(speed, eEnemyType::SHOOT)
{
	float enemyY = randomFloat(100, 400);

	m_position.x = ScreenWidth;
	m_position.y = enemyY;
}

void ShootEnemy::shoot()
{
	std::unique_ptr<Projectile> projPtr;
	
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{0.f, ShootEnemyProjSpeed});

    m_projVec.push_back(std::move(projPtr));
}

bool ShootEnemy::isProjOOB(Projectile* proj)
{
	sf::FloatRect bounds = proj->getShape().getGlobalBounds();

	if (bounds.position.x < 0 || bounds.position.x + bounds.size.x > ScreenWidth)
		return true;
	else if (bounds.position.y < 0 || bounds.position.y + bounds.size.y > GroundLevel)
		return true;

	return false;
}

void ShootEnemy::update(float dt)
{

	if (m_shootStartClock.getElapsedTime().asSeconds() > ShootEnemyFireInterval && !m_isShooting)
	{
		m_isShooting = true;
		m_shootEffectClock.restart();
	}

	if (m_isShooting)
	{

		if (m_shootEffectClock.getElapsedTime().asSeconds() > ShootEnemyFireEffectTime / 2 && !m_hasShot)
		{
			shoot();
			m_hasShot = true;
		}

		if (m_shootEffectClock.getElapsedTime().asSeconds() > ShootEnemyFireEffectTime)
		{
			m_isShooting = false;
			m_hasShot = false;
			m_shootStartClock.restart();
		}
	}
	else
	{
		m_position.x -= m_speed * dt;
		m_pSprite->setPosition(m_position);
	}

	for (size_t i = 0; i < m_projVec.size(); ++i)
	{
		m_projVec[i]->update(dt);

		if (isProjOOB(m_projVec[i].get()))
		{
			std::swap(m_projVec[i], m_projVec.back());
			m_projVec.pop_back();
			continue;
		}
	}

}

void ShootEnemy::render(sf::RenderTarget& target) const
{
	target.draw(*m_pSprite);

	for (auto& proj : m_projVec)
	{
		proj->render(target);
	}
}
