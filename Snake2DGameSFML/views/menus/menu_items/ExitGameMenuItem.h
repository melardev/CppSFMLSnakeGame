#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "MenuItem.h"

class ExitMenuItem : public MenuItem
{
public:
	
	ExitMenuItem(sf::RenderWindow* screen, GameView gameView, int charSize);
	~ExitMenuItem();
	sf::RenderWindow* screen;
};
