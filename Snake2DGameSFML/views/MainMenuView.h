#pragma once
#include "MenuView.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

namespace sf
{
	class RenderWindow;
}

class MainMenuView : public MenuView
{
public:
	explicit MainMenuView(sf::RenderWindow* screen);
	~MainMenuView();

private:
	sf::Text mainMenuText;
	sf::Font mainMenuFont;
};
