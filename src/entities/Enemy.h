#pragma once

#include "Entity.h"
#include "Constants.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum eEnemyType
{
	GROUND,
	AIR,
	SHOOT
};

namespace sf { class Sprite; }

class Enemy : public Entity
{

public:

    Enemy() = default;
	Enemy(float speed, eEnemyType type);
    virtual ~Enemy() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

protected:

	float m_speed = GroundEnemyBaseSpeed;
	eEnemyType m_type = GROUND;
};
