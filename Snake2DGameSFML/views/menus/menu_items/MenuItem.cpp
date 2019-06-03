#include "MenuItem.h"
#include <SFML/Graphics/RenderWindow.hpp>


MenuItem::MenuItem(sf::RenderWindow* window, GameView font, const sf::String& text,
                   unsigned int charSize = 40): screen(window)
{
	caption = new TextWidget(font, text, charSize);

	caption->setPosition(100.f, 100.f);

	normalColor = sf::Color::Cyan;
	hoverColor = sf::Color::Yellow;
	activeColor = sf::Color::Green;
	isHovered = false;
	isActive = false;
}

MenuItem::~MenuItem()
{
	delete caption;
}

void MenuItem::setFont(const sf::Font& font)
{
	caption->setFont(font);
}

void MenuItem::setTextSize(int textSize)
{
	caption->setCharacterSize(textSize);
}

void MenuItem::setPosition(float x, float y) const
{
	caption->setPosition(x, y);
}

void MenuItem::setPosition(const sf::Vector2f& vec) const
{
	caption->setPosition(vec.x, vec.y);
}


bool MenuItem::contains(const sf::Vector2f& coordinates) const
{
	return caption->getGlobalBounds().contains(coordinates);
}

void MenuItem::draw()
{
	sf::Color color;
	if (isHovered)
	{
		color = hoverColor;
	}
	else if (isActive)
	{
		color = activeColor;
	}
	else
	{
		color = normalColor;
	}

	caption->setFillColor(color);
	caption->drawText(screen);
}

void MenuItem::drawHover()
{
	caption->setFillColor(hoverColor);
	caption->drawText(screen);
}

float MenuItem::getWidth() const
{
	return caption->getGlobalBounds().width;
}

float MenuItem::getHeight() const
{
	return caption->getGlobalBounds().height;
}

void MenuItem::setHoveredState(bool isHovered)
{
	this->isHovered = isHovered;
}

void MenuItem::onMouseMove(const sf::Vector2f& mouse)
{
	if (contains(mouse))
	{
		if (!isActive)
			setHoveredState(true);
	}
	else
	{
		setHoveredState(false);
	}
}

void MenuItem::setActiveState(bool active)
{
	this->isActive = active;
}

void MenuItem::onLMouseDown(const sf::Vector2f& mouse)
{
	if (contains(mouse))
	{
		setActiveState(true);
		setHoveredState(false);
	}
	else
	{
		setActiveState(false);
		setHoveredState(false);
	}
}

void MenuItem::onLMouseUp(const sf::Vector2f mouse)
{
	// no matter where the mouse is, if we don't press the Left mouse button
	// the active state is set to false
	setActiveState(false);


	if (contains(mouse))
		setHoveredState(true);
}
