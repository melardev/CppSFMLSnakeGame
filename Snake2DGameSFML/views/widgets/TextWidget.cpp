#include "TextWidget.h"
#include <SFML/System/String.hpp>
#include "../../Game.h"

TextWidget::TextWidget(GameView fontForView, const sf::String& caption, unsigned int charSize, const sf::Vector2i& pos,
                       const sf::Color& fillColor)
{
	font = game->getFont(fontForView);
	setFont(font);
	setString(caption);
	setCharacterSize(charSize);
	setFillColor(fillColor);
	setPosition(pos.x, pos.y);
}

void TextWidget::drawText(sf::RenderWindow* renderWindow) const
{
	renderWindow->draw(*this);
}
