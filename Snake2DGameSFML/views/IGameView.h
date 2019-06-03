#pragma once

class IGameView
{
public:
	IGameView();
	virtual ~IGameView();

	virtual void loop() = 0;
};
