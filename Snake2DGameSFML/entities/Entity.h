#pragma once
#include <SFML/System/Vector2.hpp>
#include "../game_defs.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void draw() = 0;

	virtual void setPosition(const sf::Vector2i& vectorMovement) = 0;
	virtual void update(const AppOrientation& movement) =0;
	virtual bool collide(const sf::Vector2i& vector2) =0;
};
