#include "StartGameMenuItem.h"

StartGameMenuItem::StartGameMenuItem(sf::RenderWindow* screen, GameView gameView, int charSize)
	: MenuItem(screen, gameView, "Start Game", charSize), screen(screen)
{
}

StartGameMenuItem::~StartGameMenuItem()
{
}
