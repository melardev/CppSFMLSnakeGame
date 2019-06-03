#include "GameOverView.h"
#include "../Game.h"
#include "menus/GameOverMenu.h"

GameOverView::GameOverView(sf::RenderWindow* screen) : MenuView(new GameOverMenu(screen))
{
}

GameOverView::~GameOverView()
{
}
