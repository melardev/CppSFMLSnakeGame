#include "Menu.h"
#include "../../Game.h"
#include "menu_items/MenuItem.h"


Menu::Menu(sf::RenderWindow* wnd)
{
	renderWindow = wnd;
}

void Menu::onMenuItemClicked(MenuItem* actionMenu, int index)
{
	// No op, for functionality we have to override it in subclasses
	// throw NotImplementedException();
}


bool Menu::update()
{
	sf::Event event{};
	const sf::Vector2f mouse(sf::Mouse::getPosition(*renderWindow));
	while (renderWindow->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			game->onExitGame();
			return false;
		}

		for (unsigned int index = 0; index < menuItems.size(); ++index)
		{
			MenuItem* menuItem = menuItems.at(index);
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					menuItem->onLMouseUp(mouse);
					if (menuItem->contains(mouse))
					{
						selectedMenuItemIndex = index;
						selectedMenuItem = menuItem;
						onMenuItemClicked(menuItem, index);
						return false;
					}
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					menuItem->onLMouseDown(mouse);
				}
			}
			else if (event.type == sf::Event::MouseMoved)
			{
				menuItem->onMouseMove(mouse);
			}
		}
	}
	return true;
}


void Menu::render()
{
	renderWindow->clear(sf::Color::Black);
	TextWidget* mainMenuText = getMainTextForMenu();
	if (mainMenuText != nullptr)
		mainMenuText->drawText(renderWindow);

	for (auto iterator = menuItems.begin(); iterator != menuItems.end(); ++iterator)
	{
		MenuItem* item = *iterator;
		(*iterator)->draw();
	}
	renderWindow->display();
}

std::vector<MenuItem*> Menu::getMenuItems() const
{
	return menuItems;
}

void Menu::addMenuItem(MenuItem* menuItem)
{
	menuItems.push_back(menuItem);
}

TextWidget* Menu::getMainTextForMenu()
{
	return nullptr;
}
