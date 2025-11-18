#pragma once

#include "IState.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "EnemySpawner.h"
#include "PlatformHandler.h"
#include "ScoreHandler.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class StatePlaying : public IState
{
public:
    StatePlaying(StateStack& stateStack);
    ~StatePlaying() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	void checkEnemyCollisionAndOOB();
	void drawSpikeWall(sf::RenderTarget& target) const;
	void handleGroundDissappear();
	void handleGroundBlinking();

    StateStack& m_stateStack;
    std::unique_ptr<EnemySpawner> m_pEnemySpawner;
	std::unique_ptr<PlatformHandler> m_pPlatformHandler;
    std::unique_ptr<Player> m_pPlayer;
    std::unique_ptr<ScoreHandler> m_pScoreHandler;

	std::unique_ptr<sf::Sprite> m_spikeSprite;

    std::vector<std::unique_ptr<Enemy>> m_enemies;
    sf::RectangleShape m_ground;
    bool m_hasPauseKeyBeenReleased = true;

	sf::Clock m_groundDissappearClock;
	sf::Clock m_groundBlinkClock;
	bool m_hasGround = true;
	bool m_isGroundVisible = true;
	bool m_isGroundBlinking = false;
	float m_prevBlink = 0.0f;

	const sf::Font* m_pFont;

	bool m_hasEnded = false;

};
