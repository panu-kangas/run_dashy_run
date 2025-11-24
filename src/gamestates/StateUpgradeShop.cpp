#include "StateUpgradeShop.h"
#include "StatePlaying.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include "Constants.h"
#include "utils.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>

StateUpgradeShop::StateUpgradeShop(StateStack& stateStack, GameData& gameData)
    : m_stateStack(stateStack), m_gameData(gameData)
{

	float buttonSizeX = 600.f;
	float buttonSizeY = 120.f;
	float buttonPosX = ScreenWidth / 2 - buttonSizeX / 2;
	m_greenColor = sf::Color(7, 179, 13, 200);
	sf::Color buttonBgColor(227, 203, 66, 200);

	m_turboJumpUpgradeBtn.setSize({buttonSizeX, buttonSizeY});
	if (m_gameData.hasTurboUpgrade)
		m_turboJumpUpgradeBtn.setFillColor(m_greenColor);
	else
		m_turboJumpUpgradeBtn.setFillColor(buttonBgColor);
	m_turboJumpUpgradeBtn.setPosition({buttonPosX, 400});
	m_turboJumpUpgradeBtn.setOutlineThickness(m_activeOutlineThickness);

	m_dashUpgradeBtn.setSize({buttonSizeX, buttonSizeY});
	m_dashUpgradeBtn.setFillColor(buttonBgColor);
	if (m_gameData.hasDashUpgrade)
		m_dashUpgradeBtn.setFillColor(m_greenColor);
	else
		m_dashUpgradeBtn.setFillColor(buttonBgColor);
	m_dashUpgradeBtn.setPosition({buttonPosX, 550});

	m_continueBtn.setSize({400, 80});
	m_continueBtn.setFillColor(m_greenColor);
	m_continueBtn.setPosition({ScreenWidth / 2 - 200, ScreenHeight - 200});
}

void StateUpgradeShop::initText(std::unique_ptr<sf::Text>& ptr, std::string text, float charSize, sf::Color color, sf::FloatRect btnBounds)
{
	ptr = std::make_unique<sf::Text>(*m_pFont, text);
	ptr->setCharacterSize(charSize);
	ptr->setFillColor(color);
	float textPosX = btnBounds.position.x + btnBounds.size.x / 2 - ptr->getGlobalBounds().size.x / 2;
	float textPosY = btnBounds.position.y + 10;
	ptr->setPosition({textPosX, textPosY});
}


bool StateUpgradeShop::init()
{
    m_pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
    if (m_pFont == nullptr)
	{
        return false;
	}

	sf::Color headerColor(sf::Color::Black);
	sf::Color normalTextColor(sf::Color(60, 60, 60));
	sf::FloatRect turboBtnBounds = m_turboJumpUpgradeBtn.getGlobalBounds();
	sf::FloatRect dashBtnBounds = m_dashUpgradeBtn.getGlobalBounds();
	sf::FloatRect continueBtnBounds = m_continueBtn.getGlobalBounds();

	initText(m_turboBtnHeaderText, "Upgrade Turbo Jump", 30, headerColor, turboBtnBounds);

	initText(m_turboBtnDescriptionText, "Makes turbo jump loading time shorter", 20, normalTextColor, turboBtnBounds);
	float descriptionTextPosX = turboBtnBounds.position.x + turboBtnBounds.size.x / 2 - m_turboBtnDescriptionText->getGlobalBounds().size.x / 2;
	float descriptionTextPosY = turboBtnBounds.position.y + turboBtnBounds.size.y / 2;
	m_turboBtnDescriptionText->setPosition({descriptionTextPosX, descriptionTextPosY});

	initText(m_turboBtnPriceText, std::to_string(m_turboUpgradePrice) + " coins", 20, normalTextColor, turboBtnBounds);
	float priceTextPosX = turboBtnBounds.position.x + 10;
	float priceTextPosY = turboBtnBounds.position.y + 10;
	m_turboBtnPriceText->setPosition({priceTextPosX, priceTextPosY});

	initText(m_dashBtnHeaderText, "Upgrade Dash", 30, headerColor, dashBtnBounds);

	initText(m_dashBtnDescriptionText, "Adds a laser beam attack to Dashy's dash", 20, normalTextColor, dashBtnBounds);
	descriptionTextPosX = dashBtnBounds.position.x + dashBtnBounds.size.x / 2 - m_dashBtnDescriptionText->getGlobalBounds().size.x / 2;
	descriptionTextPosY = dashBtnBounds.position.y + dashBtnBounds.size.y / 2;
	m_dashBtnDescriptionText->setPosition({descriptionTextPosX, descriptionTextPosY});

	initText(m_dashBtnPriceText, std::to_string(m_dashUpgradePrice) + " coins", 20, normalTextColor, dashBtnBounds);
	priceTextPosX = dashBtnBounds.position.x + 10;
	priceTextPosY = dashBtnBounds.position.y + 10;
	m_dashBtnPriceText->setPosition({priceTextPosX, priceTextPosY});

	initText(m_continueBtnText, "Continue to Game", 30, headerColor, continueBtnBounds);
	float continueTextPosX = continueBtnBounds.position.x + continueBtnBounds.size.x / 2 - m_continueBtnText->getGlobalBounds().size.x / 2;
	float continueTextPosY = continueBtnBounds.position.y + continueBtnBounds.size.y / 2 - m_continueBtnText->getGlobalBounds().size.y / 2 - 10.f;
	m_continueBtnText->setPosition({continueTextPosX, continueTextPosY});

    return true;
}

void StateUpgradeShop::update(float dt)
{
    (void)dt;

	// PRESSES
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		if (m_turboJumpUpgradeBtn.getOutlineThickness() > 0 && !m_gameData.hasTurboUpgrade 
		&& m_gameData.playerCoins >= m_turboUpgradePrice)
		{
			m_gameData.playerCoins -= m_turboUpgradePrice;
			m_gameData.hasTurboUpgrade = true;
			m_turboJumpUpgradeBtn.setFillColor(m_greenColor);
		}
		else if (m_dashUpgradeBtn.getOutlineThickness() > 0 && !m_gameData.hasDashUpgrade 
		&& m_gameData.playerCoins >= m_dashUpgradePrice)
		{
			m_gameData.playerCoins -= m_dashUpgradePrice;
			m_gameData.hasDashUpgrade = true;
			m_dashUpgradeBtn.setFillColor(m_greenColor);
		}
		else if (m_continueBtn.getOutlineThickness() > 0)
		{
			m_turboJumpUpgradeBtn.setOutlineThickness(m_activeOutlineThickness);
			m_dashUpgradeBtn.setOutlineThickness(0);
			m_continueBtn.setOutlineThickness(0);
			m_stateStack.push<StatePlaying>();
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_stateStack.popDeferred();
	}

	if (!m_sHold && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_sHold = true;
		if (m_turboJumpUpgradeBtn.getOutlineThickness() > 0)
		{
			m_turboJumpUpgradeBtn.setOutlineThickness(0);
			m_dashUpgradeBtn.setOutlineThickness(m_activeOutlineThickness);
		}
		else if (m_dashUpgradeBtn.getOutlineThickness() > 0)
		{
			m_dashUpgradeBtn.setOutlineThickness(0);
			m_continueBtn.setOutlineThickness(m_activeOutlineThickness);
		}
	}

	if (!m_wHold && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_wHold = true;
		if (m_continueBtn.getOutlineThickness() > 0)
		{
			m_continueBtn.setOutlineThickness(0);
			m_dashUpgradeBtn.setOutlineThickness(m_activeOutlineThickness);
		}
		else if (m_dashUpgradeBtn.getOutlineThickness() > 0)
		{
			m_dashUpgradeBtn.setOutlineThickness(0);
			m_turboJumpUpgradeBtn.setOutlineThickness(m_activeOutlineThickness);
		}
	}


	// RELEASES
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_wHold = false;
	}
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_sHold = false;
	}


}

void StateUpgradeShop::render(sf::RenderTarget& target) const
{
	drawHeaderText(m_pFont, target, "Welcome to Upgrade Shop!");
	drawCenteredText(m_pFont, target, "Here you can use the precious coins you've earned to upgrade Dashy!", - 340.f);
	drawCenteredText(m_pFont, target, "Use WASD and Enter to navigate the menu, press ESC to return to the Interactive Introduction", - 280.f, true);

	drawCenteredText(m_pFont, target, "Your coins: " + std::to_string(m_gameData.playerCoins), - 180.f, true);

	target.draw(m_continueBtn);
	target.draw(m_turboJumpUpgradeBtn);
	target.draw(m_dashUpgradeBtn);

	target.draw(*m_continueBtnText);

	target.draw(*m_turboBtnHeaderText);
	target.draw(*m_turboBtnDescriptionText);
	target.draw(*m_turboBtnPriceText);

	target.draw(*m_dashBtnHeaderText);
	target.draw(*m_dashBtnDescriptionText);
	target.draw(*m_dashBtnPriceText);

}