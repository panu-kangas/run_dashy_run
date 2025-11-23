#include <Coin.h>
#include "Constants.h"

Coin::Coin(sf::Vector2f position, int value)
{
	m_position = position;
	m_value = value;

	m_shape.setFillColor(sf::Color::Yellow);
	m_shape.setRadius(20.f);
	sf::FloatRect localBounds = m_shape.getLocalBounds();
    m_shape.setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
	m_shape.setPosition(m_position);
}


void Coin::update(float dt)
{
	m_position.x -= CoinInitSpeed * dt;
	m_shape.setPosition(m_position);
}


void Coin::render(sf::RenderTarget& target)
{
	target.draw(m_shape);
}