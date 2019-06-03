#include "../game_defs.h"
#include "MainMenuView.h"
#include "menus/MainMenu.h"


MainMenuView::MainMenuView(sf::RenderWindow* screen) : MenuView(new MainMenu(screen))
{
}

MainMenuView::~MainMenuView()
{
}
