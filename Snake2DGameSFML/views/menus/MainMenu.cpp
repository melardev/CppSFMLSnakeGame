#include "MainMenu.h"
#include "../../Game.h"
#include "menu_items/StartGameMenuItem.h"
#include "menu_items/ExitGameMenuItem.h"


MainMenu::MainMenu(sf::RenderWindow* screen): Menu(screen)
{
	mainMenuText = new TextWidget(GameView::HomeMenu, "Main Menu", 60);
	mainMenuText->setPosition(
		(float)GAME_WIDTH / 2 - mainMenuText->getGlobalBounds().width / 2,
		// The code to center would be this one
		// SCREEN_HEIGTH / 2 - mainMenuText.getGlobalBounds().height / 2
		MAIN_MENU_TEXT_Y_OFFSET
	);


	menuItems.push_back(new StartGameMenuItem(screen, GameView::HomeMenu, 40));
	menuItems.push_back(new ExitMenuItem(screen, GameView::HomeMenu, 40));

	int i = 0;
	// float availableHeightForMenuItems = GAME_HEIGHT - (MAIN_MENU_TEXT_Y_OFFSET + mainMenuText->getGlobalBounds().height);


	float spacing = 50;

	for (auto menuItem : menuItems)
	{
		const float menuItemHeight = menuItem->getHeight();
		const float yOffset = MAIN_MENU_ITEM_Y_OFFSET +
			(menuItemHeight + (i == 0 ? 0 : MAIN_MENU_ITEM_Y_PADDING) * i);
		const float xOffset = (float)GAME_WIDTH / 2 - menuItem->getWidth() / 2; // Center in X
		menuItem->setPosition(xOffset,
		                      yOffset);
		i++;
	}

	screen->setFramerateLimit(10);
}

MainMenu::~MainMenu()
{
	delete mainMenuText;
	for (auto menuItem : menuItems)
	{
		delete menuItem;
	}
}

void MainMenu::onMenuItemClicked(MenuItem* actionMenu, int index)
{
	if (index == 0)
		game->onStartGame();
	else if (index == 1)
		game->onExitGame();
	running = false;
}

TextWidget* MainMenu::getMainTextForMenu()
{
	return mainMenuText;
}
