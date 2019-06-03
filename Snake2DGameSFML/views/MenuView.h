#pragma once
#include "IGameView.h"

class Menu;

class MenuView : public IGameView
{
public:
	explicit MenuView(Menu* menu);
	virtual ~MenuView();
	void loop() override;
	bool running;
	Menu* menu;
};
