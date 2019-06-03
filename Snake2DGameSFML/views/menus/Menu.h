#pragma once
#include <SFML/Graphics.hpp>

class TextWidget;
class MenuItem;

class Menu
{
public:
	Menu()
	{
	};
	Menu(sf::RenderWindow* wnd);
	virtual ~Menu() = default;

	virtual void onMenuItemClicked(MenuItem* actionMenu, int index);

	bool update();
	void render();

	virtual TextWidget* getMainTextForMenu();

	std::vector<MenuItem*> getMenuItems() const;
	void addMenuItem(MenuItem* menuItem);


protected:

	sf::RenderWindow* renderWindow;
	sf::String menuTitle;

	// sf::Font MenuItemFont;
	sf::Font MenuTitleFont;
	std::vector<MenuItem*> menuItems;
	bool running;
	unsigned int selectedMenuItemIndex = 0;

	MenuItem* selectedMenuItem;
};
