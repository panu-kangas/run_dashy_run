#pragma once

#include <SFML/Graphics/CircleShape.hpp>

class Coin
{

public:

	Coin(sf::Vector2f position, int value);

	void update(float dt);
	void render(sf::RenderTarget& target);

	sf::CircleShape& getShape() { return m_shape; };
	int getValue() { return m_value; };

private:

	sf::CircleShape m_shape;
	int m_value = 0;

	sf::Vector2f m_position;

};