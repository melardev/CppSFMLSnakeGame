#pragma once
#include <SFML/Graphics.hpp>
#include "Food.h"
#include "../utils/random.h"

namespace sf
{
	class RenderWindow;
}



class Snake : public Entity
{
public:
	Snake(sf::RenderWindow* display);
	~Snake();

	void draw() override;
	bool died();
	bool ateFood(Food* food);
	bool collide(const sf::Vector2i& loc) override;

	void dumpHeadPosition() const;
	void dumpBodyPartsPositions();
	void dumpPositions();
	virtual void update(const AppOrientation& orientation) override;
	const sf::Vector2f getHeadPosition() const;

	virtual void setPosition(const sf::Vector2i& vectorMovement) override;
	void resetState();
private:
	sf::RenderWindow* screen;
	Random* random;

	AppOrientation currentOrientation;

	std::vector<sf::RectangleShape> body;
	sf::RectangleShape head;
	sf::Color colorBody;
	sf::Color colorHead;

	float speed;
};
