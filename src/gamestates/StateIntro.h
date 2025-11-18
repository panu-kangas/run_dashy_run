#pragma once

#include "IState.h"
#include "entities/Player.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

class Player;

namespace sf { class Text; };

class StateIntro : public IState
{
public:
    StateIntro(StateStack& stateStack);
    ~StateIntro() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

public:
    StateStack& m_stateStack;
	const sf::Font* m_pFont;
    bool m_hasStartKeyBeenPressed = false;
    bool m_hasStartKeyBeenReleased = false;

	sf::RectangleShape m_ground;

	std::unique_ptr<Player> m_pPlayer;

};