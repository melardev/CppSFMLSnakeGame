#include "GameOverMenu.h"
#include "../../Game.h"
#include "menu_items/MenuItem.h"


#define MENU_ITEM_Y_PADDING 20.f
#define GAME_OVER_Y_OFFSET 100.f

GameOverMenu::GameOverMenu(sf::RenderWindow* renderWindow) : Menu(renderWindow),
                                                             gameOverText(
	                                                             TextWidget(GameView::GameOver, "Game\nOver", 200))
{
	gameOverText.setPosition(
		(float)GAME_WIDTH / 2 - gameOverText.getGlobalBounds().width / 2,
		// GAME_HEIGHT / 2 - gameOverText.getGlobalBounds().height / 2
		GAME_OVER_Y_OFFSET);

	MenuItem* startMenuItem = new MenuItem(renderWindow, GameView::GameOver, "Restart", 40);
	MenuItem* exitMenuItem = new MenuItem(renderWindow, GameView::GameOver, "Exit", 40);


	menuItems.push_back(startMenuItem);
	menuItems.push_back(exitMenuItem);


	int i = 0;
	const float yBaseOffset = GAME_OVER_Y_OFFSET + gameOverText.getGlobalBounds().height;

	const float spacing = 50;

	for (auto menuItem : menuItems)
	{
		const float menuItemHeight = menuItem->getHeight();
		const float yOffset = yBaseOffset + spacing * 2 /*just magic numbers*/ + (menuItemHeight + spacing * i);
		const float xOffset = GAME_WIDTH / 2 - menuItem->getWidth() / 2; // Center in X
		menuItem->setPosition(xOffset, yOffset);
		i++;
	}

	renderWindow->setFramerateLimit(40);
}

GameOverMenu::~GameOverMenu()
{
}


void GameOverMenu::onMenuItemClicked(MenuItem* actionMenu, int index)
{
	if (index == 0) // Restart Game
		game->onStartGame();
	else if (index == 1)
		game->onExitGame();
}

TextWidget* GameOverMenu::getMainTextForMenu()
{
	return &gameOverText;
}
