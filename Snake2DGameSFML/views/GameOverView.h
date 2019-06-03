#pragma once
#include "MenuView.h"

namespace sf {
	class RenderWindow;
}

class GameOverView : public MenuView
{
public:
	explicit GameOverView(sf::RenderWindow* screen);
	~GameOverView();
};
