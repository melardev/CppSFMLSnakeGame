#include "Snake.h"
#include "../Game.h"
#include <iostream>
#include "../utils/vec_utils.h"

#define DEFAULT_DIRECTION AppOrientation::Left
#define DEFAULT_SNAKE_BODY_PARTS 5

Snake::Snake(sf::RenderWindow* display) : screen(display)
{
	random = Random::getInstance();
	colorBody = sf::Color::Green;
	colorHead = sf::Color::Cyan;

	speed = 1 * TILE_SIZE;
	resetState();
}

Snake::~Snake()
{
}

void Snake::update(const AppOrientation& orientation)
{
	// If the user presses down while he is going upwards or downwards then it is in the same direction
	// so the orientation will not be changed
	bool differentDirection = true;
	if ((currentOrientation == AppOrientation::Up || currentOrientation == AppOrientation::Down)
		&&
		(orientation == AppOrientation::Up || orientation == AppOrientation::Down))
	{
		differentDirection = false;
	}


	if ((currentOrientation == AppOrientation::Left || currentOrientation == AppOrientation::Right) &&
		(orientation == AppOrientation::Left || orientation == AppOrientation::Right))
	{
		differentDirection = false;
	}


	if (orientation != AppOrientation::NoMovement && differentDirection)
	{
		currentOrientation = orientation;
	}

	const sf::Vector2f oldHeadPosition = head.getPosition();
	head.setPosition((int)oldHeadPosition.x + orientationMap[currentOrientation].x * TILE_SIZE,
	                 (int)oldHeadPosition.y + orientationMap[currentOrientation].y * TILE_SIZE);

	// dumpPositions();

	const size_t iterations = body.size() - 1;
	for (unsigned int i = iterations; i >= 0; i--)
	{
		if (i == 0)
		{
			body[0].setPosition(oldHeadPosition);
			// std::cout << "Body[" << i << "] (" << body[i].getPosition().x << ", " << body[i].getPosition().y << ") " << std::endl;
			break;
		}
		// If you plan to use temporary variables, make sure to retrieve each body[i] by reference!
		// Look at the for loop below using iterators I have explained why
		body[i].setPosition(body[i - 1].getPosition());
		// std::cout << "Body[" << i << "] (" << body[i].getPosition().x << ", " << body[i].getPosition().y << ") " << std::endl;
	}

	return;
	// This is how I did it at the beginning with iterators, too much code in my opinion
	// I let it for education purposes
	std::vector<sf::RectangleShape>::iterator listIterator1;
	std::vector<sf::RectangleShape>::iterator listIterator2;
	for ( // Initialization
		listIterator1 = body.end() - 1,
		listIterator2 = body.end() - 2;
			// Condition
		listIterator1 >= body.begin();
			// Step
		--listIterator1
	)
	{
		// Please notice the & for currentParticle, we want to change
		// the particle position itself, not a COPY of the particle.
		// so we retrieve it by reference
		sf::RectangleShape& currentParticle = (*listIterator1);
		if (listIterator1 == body.begin())
		{
			currentParticle.setPosition(oldHeadPosition);
			break;
		}

		// We could obtain a copy, it does not matter, we are not changing it
		// but for performance, obtain the reference
		sf::RectangleShape& prevParticle = (*listIterator2);
		const sf::Vector2f currentPos = currentParticle.getPosition();


		sf::Vector2f prevPos = prevParticle.getPosition();
		currentParticle.setPosition(prevPos);

		if (listIterator2 != body.begin())
			--listIterator2;
	}
}

const sf::Vector2f Snake::getHeadPosition() const
{
	return head.getPosition();
}

void Snake::setPosition(const sf::Vector2i& position)
{
	// Not used ...
	return;
}

void Snake::resetState()
{
	// Get random position being X: [1/4 , 3/4] , basically in the middle half of the screen
	// The same for Y, in the middle half of the screen in the Y axis
	// (size().x * 3/4) is the same as (size().x/4)  * 3 
	// just in case you didn't understand the below code.
	const int randomX = random->getRandomInt(screen->getSize().x / 4, screen->getSize().x * 3 / 4);;
	const int randomY = random->getRandomInt(screen->getSize().y / 4, screen->getSize().y * 3 / 4);

	// randomX and randomY may have any integer value, but we can not use any value
	// our x and y should be multiple of TILE_SIZE, so let's retrieve the top left position
	// of the tile that contains the randomX and randomY and that pos will be the one used for the head
	
	const sf::Vector2i tileTopLeft = Game::getTileTopLeftForPos(randomX, randomY);
	const int xHead = tileTopLeft.x;
	const int yHead = tileTopLeft.y;
	
	head = game->buildTile(xHead, yHead, colorHead);

	body.clear();

	// Create body particles to the right
	for (unsigned int i = 0; i < DEFAULT_SNAKE_BODY_PARTS; i++)
		body.push_back(Game::buildTile(sf::Vector2i(xHead + TILE_SIZE * (i + 1), yHead + TILE_SIZE * 0), colorBody));

	currentOrientation = DEFAULT_DIRECTION;
}

void Snake::draw()
{
	screen->draw(head);
	for (unsigned int i = 0; i < body.size(); i++)
	{
		screen->draw(body[i]);
	}
}

bool Snake::died()
{
	const int x = (int)head.getGlobalBounds().left;
	const int y = (int)head.getGlobalBounds().top;
	const int sx = screen->getSize().x;
	const int sy = screen->getSize().y;

	// Out of game position check
	if (x < 0 || x > sx || y < 0 || y > sy)
		return true;

	// Self collision(head with body parts) check
	for (unsigned int i = 0; i < body.size(); ++i)
	{
		if (vectors2fCollide(head, body[i]))
			return true;
	}

	return false;
}

bool Snake::ateFood(Food* food)
{
	if (vectors2fCollide(head, food->ownShape))
	{
		// now newLocation has the same location as the last element
		const sf::Vector2f& lastParticlePosition = body[body.size() - 1].getPosition();
		const sf::Vector2i newLocation(lastParticlePosition.x, lastParticlePosition.y);
		body.push_back(Game::buildTile(newLocation, colorBody));
		// dumpPositions();
		return true;
	}
	return false;
}


bool Snake::collide(const sf::Vector2i& loc)
{
	for (unsigned int i = 0; i < body.size(); ++i)
	{
		if (body[i].getGlobalBounds().contains(loc.x, loc.y))
		{
			return true;
		}
	}
	return false;
}


void Snake::dumpPositions()
{
	dumpHeadPosition();
	dumpBodyPartsPositions();
}

void Snake::dumpHeadPosition() const
{
	std::cout << "Head (" << head.getPosition().x << ", " << head.getPosition().y << ") " << std::endl;
}

void Snake::dumpBodyPartsPositions()
{
	int index = 0;
	for (auto&& particle : body)
	{
		std::cout << "Body[" << index++ << "]: (" << particle.getPosition().x << ", " << particle.getPosition().y <<
			") " << std::endl;
	}
}


/* This was the first implementation I wrote for the ateFood, it is overcomplicated and even with that, it is not perfect
 * It is weird because the best implementation is actually the simplest one ( the one I actually use) which consists
 * on setting the new snake body part position to the same position as the latest body part. Remember, that overlapping
 * between the last and the new body parts only happen for a single frame
bool Snake::ateFood(Food* food)
{
	if (vectors2fCollide(head, food->ownShape))
	{
		// now newLocation has the same location as the last element
		const sf::Vector2f& headPosition = head.getPosition();
		const sf::Vector2f& lastParticlePosition = body[body.size() - 1].getPosition();
		int xOffset = 0;
		int yOffset = 0;

		// This whole code is to make it properly for one single frame ....
		// because the next frame even if we draw the new particle in the same
		// pos as the latest one, it will be fixed in the next frame
		// but let's try to improve the code and make this single frame matter.

		// since we don't want overlap
		// we adjust the position of the new body particle according to the orientation
		// and the last and before last element, the algorithm is not perfect, it has some flaws
		// but anyways it is one single frame
		if (currentOrientation == AppOrientation::Up || currentOrientation == AppOrientation::Down)
		{
			bool wholeSnakeIsVertical = true;
			for (auto&& particle : body)
			{
				if (particle.getPosition().x != headPosition.x)
				{
					wholeSnakeIsVertical = false;
					break;
				}
			}

			if (wholeSnakeIsVertical)
			{
				// the whole snake is vertical
				if (currentOrientation == AppOrientation::Up)
					yOffset = 1; // Add the particle at the bottom (positive Y axis)
				else
					yOffset = -1; // Add the particle at the top (negative Y axis)
			}
			else
			{
				const sf::Vector2f& beforeLastParticlePosition = body[body.size() - 2].getPosition();
				if (lastParticlePosition.y == beforeLastParticlePosition.y)
				{
					// Now we know we should add the particle either to the right or to the left
					if (headPosition.x > lastParticlePosition.x)
						xOffset = -1; // Add it to the left
					else
						xOffset = 1; // Add it to the right
				}
				else
				{
					if (currentOrientation == AppOrientation::Up)
						yOffset = 1; // To the bottom
					else
						yOffset = -1; // To the top
				}
			}
		}
		else if (currentOrientation == AppOrientation::Right || currentOrientation == AppOrientation::Left)
		{
			bool wholeSnakeIsHorizontal = true;
			for (auto&& particle : body)
			{
				if (particle.getPosition().y != headPosition.y)
				{
					wholeSnakeIsHorizontal = false;
					break;
				}
			}

			if (wholeSnakeIsHorizontal)
			{
				if (currentOrientation == AppOrientation::Right)
					xOffset = -1; // add the particle to the left (negative X axis)
				else
					xOffset = 1; // add the particle to the right (positive X axis)
			}
			else
			{
				const sf::Vector2f& beforeLastParticlePosition = body[body.size() - 2].getPosition();
				if (lastParticlePosition.x == beforeLastParticlePosition.x)
				{
					// Now we know we should add the particle either to the top or to the bottom
					if (headPosition.y > lastParticlePosition.y)
						yOffset = -1; // Add it to the top
					else
						yOffset = 1; // Add it to the bottom
				}
				else
				{
					if (currentOrientation == AppOrientation::Left)
						xOffset = 1; // To the right
					else
						xOffset = -1; // To the left
				}
			}
		}



		// std::cout << "Last Location (" << lastParticlePosition.x << ", " << lastParticlePosition.y << ")" << std::endl;


		// since we don't move by 1 pixel, but by tiles, we multiply the normalized
		// vector by TILE_SIZE

		const sf::Vector2i newLocation(lastParticlePosition.x + TILE_SIZE * xOffset,
									   lastParticlePosition.y + TILE_SIZE * yOffset);

		// std::cout << "New Location (" << newLocation.x << ", " << newLocation.y << "); normalized offset: (" << xOffset << ", " << yOffset << ")" << std::endl;

		body.push_back(game->buildTile(newLocation, colorBody));
		dumpPositions();
		return true;
	}
	return false;
}
*/
