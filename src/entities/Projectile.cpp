#include "Projectile.h"
#include "Constants.h"
#include <SFML/System/Angle.hpp>

Projectile::Projectile(sf::Vector2f position, sf::Vector2f velocity) : Entity(position, sf::degrees(0.0f))
{
	m_position = position;
	m_velocity = velocity;

	m_shape.setSize({12.f, 12.f});
	m_shape.setFillColor(sf::Color(169, 169, 169));
	sf::FloatRect localBounds = m_shape.getLocalBounds();
    m_shape.setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
	m_shape.setPosition(m_position);
}


bool Projectile::init()
{
	return true;
}


void Projectile::update(float dt)
{
	m_position += m_velocity * dt;
	m_shape.setPosition(m_position);
}


void Projectile::render(sf::RenderTarget& target) const
{
	target.draw(m_shape);
}
