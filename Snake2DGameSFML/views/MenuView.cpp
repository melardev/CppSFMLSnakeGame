#include "MenuView.h"
#include "menus/Menu.h"


MenuView::MenuView(Menu* menu) : running(false), menu(menu)
{
}

MenuView::~MenuView()
{
}

void MenuView::loop()
{
	running = true;
	while (running)
	{
		if (menu->update())
			menu->render();
		else
			break;
	}
}
