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

	void setIsDestroyed(bool status) { m_isDestroyed = status; };
	bool getIsDestroyed() { return m_isDestroyed; };

	private:

	sf::RectangleShape m_shape;
	bool m_isDestroyed = false;
	
};