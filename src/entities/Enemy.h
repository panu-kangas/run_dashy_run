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
	AIR
};

namespace sf { class Sprite; }

class Enemy : public Entity
{

public:
    static constexpr float collisionRadius = 23.0f;

    Enemy() = default;
	Enemy(float speed, eEnemyType type);
    virtual ~Enemy() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	float m_speed = GroundEnemyBaseSpeed;
	eEnemyType m_type = GROUND;
};
