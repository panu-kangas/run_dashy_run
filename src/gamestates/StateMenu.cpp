#include "StateMenu.h"
#include "StateIntro.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include "utils.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

StateMenu::StateMenu(StateStack& stateStack)
    : m_stateStack(stateStack)
{
    
}

bool StateMenu::init()
{
    m_pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
    if (m_pFont == nullptr)
        return false;

    m_pText = std::make_unique<sf::Text>(*m_pFont);
    if (!m_pText)
        return false;

    m_pText->setString("PRESS <ENTER> TO PLAY");
    m_pText->setStyle(sf::Text::Bold);
    sf::FloatRect localBounds = m_pText->getLocalBounds();
    m_pText->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});

    return true;
}

void StateMenu::update(float dt)
{
    (void)dt;
    m_hasStartKeyBeenPressed |= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    if (m_hasStartKeyBeenReleased)
    {
        m_hasStartKeyBeenPressed = false;
        m_hasStartKeyBeenReleased = false;
        m_stateStack.push<StateIntro>();
    }
    m_hasStartKeyBeenReleased |= m_hasStartKeyBeenPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
}

void StateMenu::render(sf::RenderTarget& target) const
{
	drawHeaderText(m_pFont, target, "Run Dashy, run!");
    m_pText->setPosition({ScreenWidth * 0.5f, ScreenHeight * 0.5f});
    target.draw(*m_pText);
}
