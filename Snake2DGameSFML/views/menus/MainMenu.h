#pragma once
#include "Menu.h"
#include "../widgets/TextWidget.h"

#define MAIN_MENU_ITEM_Y_OFFSET 300.f
#define MAIN_MENU_ITEM_Y_PADDING 50.f

// Forward declaration
namespace sf
{
	class RenderWindow;
}

class MenuItem;

class MainMenu : public Menu
{
public:
	MainMenu(sf::RenderWindow* screen);
	~MainMenu();

	void onMenuItemClicked(MenuItem* actionMenu, int index) override;

	TextWidget* getMainTextForMenu() override;
	TextWidget* mainMenuText;
	
};
