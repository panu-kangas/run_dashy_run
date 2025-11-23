#pragma once

#include "IState.h"
#include <memory>

namespace sf { class Text; };

class StatePaused : public IState
{
public:
    StatePaused(StateStack& stateStack, GameData& gameData);
    ~StatePaused() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

public:
    StateStack& m_stateStack;
	GameData& m_gameData;

    const IState* m_pPrevState = nullptr;
    std::unique_ptr<sf::Text> m_pText;
    bool m_hasPauseKeyBeenReleased = false;
};
