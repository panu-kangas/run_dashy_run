#pragma once

#include "Entity.h"
#include "Constants.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class Sprite; }

class Player final : public Entity
{

public:
    static constexpr float collisionRadius = 23.0f;

    Player();
    virtual ~Player() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

	void onPlatformCollision();
	void setOnPlatform(float posY, int platformIdx);
	void removeFromPlatform();
	bool isOnPlatform() { return m_isOnPlatform; };

	bool isDashing() { return m_meteorAttack || m_isDashing; };
	void resetDash();
	bool isMeteorAttacking() { return m_meteorAttack; };

	bool isInAir() { return m_isInAir; };
	void setFallsThroughGround(bool status) { m_fallsThroughGround = status; };

	void checkCameraShake(sf::RenderTarget& target);

	sf::Vector2f getPrevPosition() { return m_prevPos; };
	sf::Vector2f getSize();
	sf::FloatRect getGlobalBounds();

private:

	void handleInput();
	void checkJumps(bool wPressed);
	void checkTurboJump(bool sPressed);
	void checkMeteorAttack(bool sPressed);
	void checkDash(bool spacePressed);
	void handleSideMovement(bool aPressed, bool dPressed);
	void applyGravity(float dt);
	void checkGrounded();
	void checkOutOfBounds();
	void checkTimers();

	void updateJumpLoadBar();

	bool handleCameraShake(sf::RenderTarget& target);
	bool m_cameraShake = false;
	std::vector<sf::Vector2f> m_shakeOffsets = {
		{4, 4}, {-4, -4}, {4, -4}, {-4, 4},
		{4, 4}, {-4, -4}, {4, -4}, {-4, 4}
	};
	size_t m_shakeIdx = 0;
	sf::Clock m_shakeTimer;
	float m_shakeInterval = 0.04f;

	bool m_isInAir = false;
	bool m_didDoubleJump = false;
	bool m_isTurboJumping = false;
	bool m_isLoadingTurbo = false;
	bool m_meteorAttack = false;
	bool m_canDash = true;
	bool m_isDashing = false;
	bool m_wHold = false;
	bool m_sHold = false;
	bool m_spaceHold = false;
	bool m_facingLeft = false;
	bool m_outlineActive = true;
	bool m_fallsThroughGround = false;

	bool m_isOnPlatform = false;
	int m_curPlatformIdx = -1;

	float m_speed = PlayerSpeed;
	sf::Vector2f m_prevPos;

	sf::Clock m_turboLoadClock;
	sf::Clock m_turboEffectClock;
	sf::Clock m_dashEffectClock;
	sf::Clock m_dashCooldownClock;

	sf::CircleShape m_playerOutlines;

	sf::RectangleShape m_jumpLoadBar;
	sf::Color m_playerNormalColor;

};
