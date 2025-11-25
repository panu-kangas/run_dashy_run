#pragma once

#include "IState.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

namespace sf { class Text; };

class StateUpgradeShop : public IState
{
public:
	StateUpgradeShop() = delete;
    StateUpgradeShop(StateStack& stateStack, GameData& gameData);
    ~StateUpgradeShop() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:

	void initText(std::unique_ptr<sf::Text>& ptr, std::string text, float charSize, sf::Color color, sf::FloatRect btnBounds);

    StateStack& m_stateStack;
	GameData& m_gameData;

	const sf::Font* m_pFont;
	sf::Color m_greenColor;

	sf::RectangleShape m_continueBtn;
	std::unique_ptr<sf::Text> m_continueBtnText;

	sf::RectangleShape m_turboJumpUpgradeBtn;
	sf::RectangleShape m_dashUpgradeBtn;

	std::unique_ptr<sf::Text> m_turboBtnHeaderText;
	std::unique_ptr<sf::Text> m_dashBtnHeaderText;

	std::unique_ptr<sf::Text> m_turboBtnDescriptionText;
	std::unique_ptr<sf::Text> m_dashBtnDescriptionText;

	std::unique_ptr<sf::Text> m_turboBtnPriceText;
	std::unique_ptr<sf::Text> m_dashBtnPriceText;

	int m_turboUpgradePrice = 1;
	int m_dashUpgradePrice = 2;

	float m_activeOutlineThickness = 3.0f;

	bool m_wHold = false;
	bool m_sHold = false;


};