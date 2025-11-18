#include "Enemy.h"
#include "ResourceManager.h"
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/CircleShape.hpp>


Enemy::Enemy(float speed, eEnemyType type)
{
	m_speed = speed;
	m_type = type;
}

bool Enemy::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("enemy.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);

	switch (m_type)
	{
		case GROUND:
		{
    		m_pSprite->setScale(sf::Vector2f(3.5f, 3.5f));
			break ;
		}

		case AIR:
		{
    		m_pSprite->setScale(sf::Vector2f(2.5f, 2.5f));
			break ;
		}

		default:
		{
			break ;
		}
	}

    m_collisionRadius = collisionRadius;

    return true;
}

void Enemy::update(float dt)
{
    m_position.x -= m_speed * dt;
}

void Enemy::render(sf::RenderTarget& target) const
{
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);
}
