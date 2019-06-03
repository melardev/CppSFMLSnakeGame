#ifndef GAME_DEF_H
#define GAME_DEF_H
#include "app_errors.h"
#include <map>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#define TILE_SIZE 20
#define GAME_WIDTH 800
#define GAME_HEIGHT 800
#define DEFAULT_SCORE_STEP 20

// The IDEs I use treat the current directory
// not where the binary is executable, but the root of the project's source code
// so I did not have to make it ../../ or whatever
// If your IDE has a different current directory you will need to adjust that
#define APP_BASE_PATH "./"


#define MAIN_MENU_TEXT_Y_OFFSET 100

enum class AppOrientation
{
	NoMovement = -1,
	Up,
	Right,
	Down,
	Left,
};

static std::map<AppOrientation, sf::Vector2i> orientationMap =
{
	{AppOrientation::Up, sf::Vector2i(0, -1)},
	{AppOrientation::Right, sf::Vector2i(1, 0)},
	{AppOrientation::Down, sf::Vector2i(0, 1)},
	{AppOrientation::Left, sf::Vector2i(-1, 0)}
};


#endif
