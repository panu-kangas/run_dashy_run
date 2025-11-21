#pragma once

#include "Entity.h"
#include <SFML/Graphics/RectangleShape.hpp>

class Projectile : public Entity
{
	public:

	Projectile() = delete;
	Projectile(sf::Vector2f position, sf::Vector2f velocity);
	~Projectile() = default;

	bool init();
    void update(float dt);
    void render(sf::RenderTarget& target) const;

	sf::RectangleShape& getShape() { return m_shape; };

	private:

	sf::RectangleShape m_shape;
	
};