#pragma once
#include "Entity.h"


class StaticEntity : public Entity
{
public:
	StaticEntity();
	~StaticEntity();

	// final to forbid subclasses overriding it
	virtual void move(sf::Vector2f vectorMovement);// final;

	void update(const AppOrientation& movement) final
	{
	}
};
