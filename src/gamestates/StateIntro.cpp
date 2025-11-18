#include "StateIntro.h"
#include "StatePlaying.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include "utils.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

StateIntro::StateIntro(StateStack& stateStack)
    : m_stateStack(stateStack)
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

	m_pPlayer = std::make_unique<Player>();
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
        m_stateStack.push<StatePlaying>();
    }
    m_hasStartKeyBeenReleased |= m_hasStartKeyBeenPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
}

void StateIntro::render(sf::RenderTarget& target) const
{
	drawHeaderText(m_pFont, target, "Welcome to the Introduction!");
	drawCenteredText(m_pFont, target, "Here is our main character, Dashy. Say hello!", - 320.f);
	drawCenteredText(m_pFont, target, "Our brave little Dashy is very talented! He can:", - 260.f);
	drawCenteredText(m_pFont, target, "- Move by using A and D keys", - 210.f, true);
	drawCenteredText(m_pFont, target, "- Jump by using W key", - 175.f, true);
	drawCenteredText(m_pFont, target, "- Double jump by using W again mid air", - 140.f, true);
	drawCenteredText(m_pFont, target, "- Turbo jump by holding down S key, while on ground", - 105.f, true);
	drawCenteredText(m_pFont, target, "- Perform a Meteor Attack my pressing S mid air", - 70.f, true);
	drawCenteredText(m_pFont, target, "- And, do a Dash by pressing Space", - 35.f, true);
	drawCenteredText(m_pFont, target, "Dashy is very powerful when dashing (space) or while performing the Meteor attack (S mid air)", 20.f, true);
	drawCenteredText(m_pFont, target, "You can even kill enemies and get points with these skills!", 55.f, true);
	drawCenteredText(m_pFont, target, "Please, spend some time learning all these moves and then press Enter to move on to the actual game", 200.f, true);


	m_pPlayer->checkCameraShake(target);

	target.draw(m_ground);

	m_pPlayer->render(target);

}