#include "Platform.h"
#include "Constants.h"
#include "entities/Player.h"

#include <iostream>

Platform::Platform(sf::Vector2f position, sf::Vector2f size, float speed)
{
	m_shape.setSize(size);
	m_shape.setPosition(position);
	m_shape.setFillColor(GroundColor);

	m_speed = speed;
}

void Platform::update(float dt)
{
	float platX = m_shape.getPosition().x + (m_speed * dt);

	m_shape.setPosition({platX, m_shape.getPosition().y});
}

void Platform::draw(sf::RenderTarget& target)
{
	target.draw(m_shape);
}

bool Platform::isPlayerOOB(Player* player)
{
	float playerLeft = player->getPosition().x - player->getSize().x / 2;
	float playerRight = playerLeft + player->getSize().x;

	if (playerLeft > m_shape.getPosition().x + m_shape.getSize().x)
	{
		return true;
	}
	else if (playerRight < m_shape.getPosition().x)
	{
		return true;
	}

	return false;
}