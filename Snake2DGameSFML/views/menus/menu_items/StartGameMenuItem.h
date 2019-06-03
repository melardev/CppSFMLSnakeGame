#pragma once
#include "MenuItem.h"

namespace sf
{
	class RenderWindow;
}

class StartGameMenuItem : public MenuItem
{
public:
	
	StartGameMenuItem(sf::RenderWindow* screen, GameView gameView, int charSize);
	~StartGameMenuItem();
	
private:
	sf::RenderWindow* screen;
};
