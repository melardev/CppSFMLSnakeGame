#pragma once
#include "../../Game.h"

class TextWidget : public sf::Text
{
public:

	TextWidget(GameView fontForView, const sf::String& caption, unsigned charSize,const sf::Vector2i& pos = sf::Vector2i(0, 0),
	           const sf::Color& fillColor = sf::Color::White);
	
	
	void drawText(sf::RenderWindow* renderWindow) const;
	
	sf::Font font;
};
