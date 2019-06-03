#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "StaticEntity.h"
class Random;

namespace sf
{
	class RenderWindow;
}

class Food : public StaticEntity
{
public:
	Food(sf::RenderWindow* screen, const sf::Vector2i& location);
	~Food();
	void draw() override;
	bool collide(const sf::Vector2i& position) override;
	void setPosition(const sf::Vector2i& vectorMovement) override;

	sf::RenderWindow* screen;
	sf::RectangleShape ownShape;
	sf::Vector2f location;
	sf::Color color;
	Random* random;
};
