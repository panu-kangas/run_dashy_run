#include "ShootEnemy.h"
#include "Constants.h"
#include "utils.h"

#include <iostream>

ShootEnemy::ShootEnemy(float speed, float shootInterval, std::vector<std::unique_ptr<Projectile>>& projVec) 
	: Enemy(speed, eEnemyType::SHOOT), m_projVec(projVec)
{
	float enemyY = randomFloat(100, 400);

	m_position.x = ScreenWidth;
	m_position.y = enemyY;
	m_shootInterval = shootInterval;
}

void ShootEnemy::shoot()
{
	std::unique_ptr<Projectile> projPtr;
	
	// Downward bullets
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{-1 * ShootEnemyProjSpeed, ShootEnemyProjSpeed});
    m_projVec.push_back(std::move(projPtr));
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{0.f, ShootEnemyProjSpeed});
    m_projVec.push_back(std::move(projPtr));
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{ShootEnemyProjSpeed, ShootEnemyProjSpeed});
    m_projVec.push_back(std::move(projPtr));

	// Upward bullets
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{-1 * ShootEnemyProjSpeed, -1 * ShootEnemyProjSpeed});
    m_projVec.push_back(std::move(projPtr));
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{0.f, -1 * ShootEnemyProjSpeed});
    m_projVec.push_back(std::move(projPtr));
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{ShootEnemyProjSpeed, -1 * ShootEnemyProjSpeed});
    m_projVec.push_back(std::move(projPtr));

	// forward
	projPtr = std::make_unique<Projectile>(m_position, sf::Vector2f{-1 * ShootEnemyProjSpeed, 0});
    m_projVec.push_back(std::move(projPtr));

}

void ShootEnemy::update(float dt)
{

	if (m_shootStartClock.getElapsedTime().asSeconds() > m_shootInterval && !m_isShooting)
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

}

void ShootEnemy::render(sf::RenderTarget& target) const
{
	target.draw(*m_pSprite);
}
