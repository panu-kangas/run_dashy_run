#include "StateIntro.h"
#include "StateUpgradeShop.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include "utils.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

StateIntro::StateIntro(StateStack& stateStack, GameData& gameData)
    : m_stateStack(stateStack), m_gameData(gameData)
{
}

bool StateIntro::init()
{
    m_pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
    if (m_pFont == nullptr)
	{
        return false;
	}

	m_ground.setSize({ScreenWidth, 256.0f});
    m_ground.setPosition({0.0f, GroundLevel});
    m_ground.setFillColor(GroundColor);

	m_pPlayer = std::make_unique<Player>(m_gameData);
    if (!m_pPlayer || !m_pPlayer->init())
	{
        return false;
	}

    m_pPlayer->setPosition(sf::Vector2f(200, GroundLevel));

    return true;
}

void StateIntro::update(float dt)
{
	m_pPlayer->update(dt);

    (void)dt;
    m_hasStartKeyBeenPressed |= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    if (m_hasStartKeyBeenReleased)
    {
        m_hasStartKeyBeenPressed = false;
        m_hasStartKeyBeenReleased = false;
        m_stateStack.push<StateUpgradeShop>();
    }
    m_hasStartKeyBeenReleased |= m_hasStartKeyBeenPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
}

void StateIntro::render(sf::RenderTarget& target) const
{
	target.draw(m_ground);

	drawHeaderText(m_pFont, target, "Welcome to the interactive Introduction!");
	drawCenteredText(m_pFont, target, "Here is our main character, Dashy. Say hello!", - 320.f);
	drawCenteredText(m_pFont, target, "Our brave little Dashy is very talented! He can:", - 260.f);
	drawCenteredText(m_pFont, target, "- Move by using A and D keys", - 210.f, true);
	drawCenteredText(m_pFont, target, "- Jump by using W key", - 175.f, true);
	drawCenteredText(m_pFont, target, "- Double jump by using W again mid air", - 140.f, true);
	drawCenteredText(m_pFont, target, "- Turbo jump by holding down S key, while on ground", - 105.f, true);
	drawCenteredText(m_pFont, target, "- Perform a Meteor Attack by pressing S mid air", - 70.f, true);
	drawCenteredText(m_pFont, target, "- And, do a Side Dash by pressing Space", - 35.f, true);
	drawCenteredText(m_pFont, target, "Dashy is very powerful when dashing (space) or while performing the Meteor attack (S mid air)", 20.f, true);
	drawCenteredText(m_pFont, target, "You can even kill enemies and get points with these skills!", 55.f, true);
	drawCenteredText(m_pFont, target, "Please, try these moves now and then press Enter to move on to the actual game", 200.f, true);
	drawCenteredText(m_pFont, target, "Oh and hey, remember to collect coins while you play!", 350.f, true);
	drawCenteredText(m_pFont, target, "You can use coins at the Upgrade Shop to upgrade Dashy's abilities", 385.f, true);

	m_pPlayer->checkCameraShake(target);

	m_pPlayer->render(target);

}