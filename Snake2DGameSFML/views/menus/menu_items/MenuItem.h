#pragma once
#include <string>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../../widgets/TextWidget.h"

namespace sf
{
	class RenderWindow;
}

class MenuItem
{
public:
	MenuItem(sf::RenderWindow* window, const sf::String& text);
	MenuItem(sf::RenderWindow* window, GameView font, const sf::String& text, unsigned charSize);
	~MenuItem();


	void setFont(const sf::Font& font);
	void setTextSize(int textSize);
	void setPosition(float x, float y) const;
	void setPosition(const sf::Vector2f& vec) const;
	bool contains(const sf::Vector2f& coordinates) const;
	void draw();
	void drawHover();
	float getWidth() const;
	float getHeight() const;
	void setHoveredState(bool isHovered);
	void onMouseMove(const sf::Vector2f& mouse);
	void setActiveState(bool active);
	
	void onLMouseUp(sf::Vector2f mouse);
	void onLMouseDown(const sf::Vector2f& mouse);

	// sf::Text caption;
	TextWidget* caption;
	sf::RenderWindow* screen;

	bool isHovered;
	bool isActive;

	sf::Color normalColor;
	sf::Color hoverColor;
	sf::Color activeColor;
};
