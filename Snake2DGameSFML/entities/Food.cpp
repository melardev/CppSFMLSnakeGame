#include "Food.h"
#include <SFML/Graphics.hpp>
#include "../Game.h"
#include <iostream>


Food::Food(sf::RenderWindow* screen, const sf::Vector2i& location) : screen(screen), location(location),
                                                                     random(Random::getInstance())
{
	color = sf::Color::Red;
	const int xRandomPos = random->getRandomInt((screen->getSize().x / 4) * 1, screen->getSize().x * 3 / 4);
	const int yRandomPos = random->getRandomInt((screen->getSize().y / 4) * 1, screen->getSize().y * 3 / 4);
	const sf::Vector2i tileTopLeftPos = Game::getTileTopLeftForPos(xRandomPos, yRandomPos);
	std::cout << "Food position " << tileTopLeftPos.x << ", " << tileTopLeftPos.y << std::endl;
	ownShape = Game::buildTile(tileTopLeftPos, color);
}

Food::~Food()
{
}

void Food::draw()
{
	screen->draw(ownShape);
}

bool Food::collide(const sf::Vector2i& position)
{
	return ownShape.getGlobalBounds().contains(position.x, position.y);
}

void Food::setPosition(const sf::Vector2i& vectorMovement)
{
	ownShape.setPosition(vectorMovement.x, vectorMovement.y);
}
