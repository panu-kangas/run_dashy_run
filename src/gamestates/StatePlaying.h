#pragma once

#include "IState.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include "entities/Projectile.h"
#include "EnemySpawner.h"
#include "PlatformHandler.h"
#include "ScoreHandler.h"
#include "CoinHandler.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class StatePlaying : public IState
{
public:
	StatePlaying() = delete;
    StatePlaying(StateStack& stateStack, GameData& gameData);
    ~StatePlaying() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	void checkEnemyCollisionAndOOB();
	void drawSpikeWall(sf::RenderTarget& target) const;
	void renderEntities(sf::RenderTarget& target) const;
	void updateEntities(float dt);
	void handleGroundDissappear();
	void handleGroundBlinking();
	bool isProjOOB(Projectile* proj);

    StateStack& m_stateStack;
	GameData& m_gameData;

    std::unique_ptr<EnemySpawner> m_pEnemySpawner;
	std::unique_ptr<PlatformHandler> m_pPlatformHandler;
    std::unique_ptr<Player> m_pPlayer;

    std::unique_ptr<ScoreHandler> m_pScoreHandler;
    std::unique_ptr<CoinHandler> m_pCoinHandler;

	std::unique_ptr<sf::Sprite> m_spikeSprite;
	std::unique_ptr<sf::Sprite> m_laserSprite;

    std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<std::unique_ptr<Projectile>> m_projVec;

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
