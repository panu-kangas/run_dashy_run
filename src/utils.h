#pragma once

#include <SFML/Graphics.hpp>
#include "Constants.h"

void drawHeaderText(const sf::Font* font, sf::RenderTarget& target, std::string str);
void drawCenteredText(const sf::Font* font, sf::RenderTarget& target, std::string str, float offset = 0, bool smallText = false);
bool checkRectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
float randomFloat(float min, float max);