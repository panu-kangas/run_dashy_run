#include <SFML/Graphics.hpp>
#include <random>
#include "Constants.h"

void drawHeaderText(const sf::Font* font, sf::RenderTarget& target, std::string str)
{
	sf::Text text(*font, str);

	text.setFillColor(HeaderTextColor);
	text.setCharacterSize(HeaderTextSize);

	float textX = ScreenWidth / 2 - text.getLocalBounds().size.x / 2;
	float textY = 40.f; 
	text.setPosition({textX, textY});

	target.draw(text);
}

void drawCenteredText(const sf::Font* font, sf::RenderTarget& target, std::string str, float offset, bool smallText)
{
	sf::Text text(*font, str);
	text.setFillColor(sf::Color::White);

	float size = 0.f;
	if (!smallText)
		size = RegularTextSize;
	else
		size = RegularTextSize - 10.f;

	text.setCharacterSize(size);

	float textX = ScreenWidth / 2 - text.getLocalBounds().size.x / 2;
	float textY = ScreenHeight / 2 - text.getLocalBounds().size.y / 2 + offset;
	text.setPosition({textX, textY});

	target.draw(text);
}

bool checkRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2) 
{
    sf::Vector2f pos1 = rect1.position;
    sf::Vector2f size1 = rect1.size;
    sf::Vector2f pos2 = rect2.position;
    sf::Vector2f size2 = rect2.size;

    return !(pos1.x + size1.x < pos2.x ||
             pos2.x + size2.x < pos1.x ||
             pos1.y + size1.y < pos2.y ||
             pos2.y + size2.y < pos1.y);
}




/**
 * 
 * This function came from ChatGPT!!
 * I read a bit about this approach and it seems legit, and gives better output than using just rand()
 * 
 */
float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distrib(min, max);
    return distrib(gen);
}