#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

inline bool vectors2fCollide(const sf::RectangleShape& loc1, const sf::RectangleShape& loc2)
{
	return loc1.getGlobalBounds().intersects(loc2.getGlobalBounds());
}

inline sf::Vector2f getRandomVector2f()
{
	Random* random = Random::getInstance();
	const int x = random->getRandomInt(0, GAME_WIDTH - 1);
	const int y = random->getRandomInt(0, GAME_HEIGHT - 1);
	return sf::Vector2f(x, y);
}
