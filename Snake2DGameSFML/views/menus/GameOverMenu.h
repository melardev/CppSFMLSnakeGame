#pragma once
#include "Menu.h"
#include "../widgets/TextWidget.h"

class GameOverMenu : public Menu
{
public:
	GameOverMenu(sf::RenderWindow* renderWindow);
	~GameOverMenu();

	void onMenuItemClicked(MenuItem* actionMenu, int index) override;
	TextWidget* getMainTextForMenu() override;

private:

	TextWidget gameOverText;
};
