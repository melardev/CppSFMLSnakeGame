#include "ExitGameMenuItem.h"


ExitMenuItem::ExitMenuItem(sf::RenderWindow* screen, GameView gameView, int charSize)
	: MenuItem(screen, gameView, "Exit Game", charSize), screen(screen)
{
}

ExitMenuItem::~ExitMenuItem()
{
}
