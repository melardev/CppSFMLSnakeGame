#include "Game.h"
#include "utils/random.h"
#include "game_defs.h"
#include <sstream>
#include "views/GameOverView.h"
#include <iostream>
#include "views/MainMenuView.h"


Game::Game(int argc, char** argv)
{
	scoreStep = DEFAULT_SCORE_STEP;
	score = 0;
	food = nullptr;
	snake = nullptr;
	scale = 0;
	screen = new sf::RenderWindow(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT),
	                              "Snake SFML C++ Game", sf::Style::Close);
	screen->setVerticalSyncEnabled(true);

	random = Random::getInstance();


	if (mainFont.loadFromFile(APP_BASE_PATH "resources/fonts/pixel/Pixel NES.otf"))
	{
		scoreTxt.setFont(mainFont);
	}

	scoreTxt.setCharacterSize(10);
	scoreTxt.setFillColor(sf::Color::Green);
	scoreTxt.setOutlineColor(sf::Color::Black);
	scoreTxt.setOutlineThickness(10.f);
	scoreTxt.setString("Score: 0");
	scoreTxt.setPosition(100.f, 10.f);
	currentView = GameView::HomeMenu;

	screen->setFramerateLimit(20);
}

Game::~Game()
{
	for (auto&& entity : entities)
		delete entity;

	delete screen;
}

void Game::start()
{
	loadResources();
	startLoop();
}

sf::RectangleShape Game::buildTile(const sf::Vector2i& loc, const sf::Color& color)
{
	sf::RectangleShape box;
	box.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	box.setPosition(loc.x, loc.y);
	box.setFillColor(color);
	return box;
}


void Game::startLoop()
{
	if (currentView == GameView::HomeMenu)
		homeMenuLoop();
	else if (currentView == GameView::Game)
		gameLoop();
	else if (currentView == GameView::GameOver)
		gameOverLoop();

	if (currentView != GameView::Exiting)
		startLoop();
}


bool Game::update()
{
	// TODO: Rewrite this code, it does seem clean to me.
	sf::Event event{};

	AppOrientation orientation = AppOrientation::NoMovement;
	while (screen->pollEvent(event))
	{
		orientation = AppOrientation::NoMovement;
		switch (event.type)
		{
		case sf::Event::KeyReleased:
			{
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					orientation = AppOrientation::Up;
					break;
				case sf::Keyboard::Right:
					orientation = AppOrientation::Right;
					break;
				case sf::Keyboard::Down:
					orientation = AppOrientation::Down;
					break;
				case sf::Keyboard::Left:
					orientation = AppOrientation::Left;
					break;
				default: break;
				}
				break;
			}
		case sf::Event::Closed:
			currentView = GameView::Exiting;
			return false;
		default:
			{
				// Left empty on purpose
			}
		}
	}

	updateEntitiesForMovement(orientation);

	if (snake->died())
	{
		currentView = GameView::GameOver;
		return false;
	}

	if (snake->ateFood(food))
	{
		score += scoreStep;
		food->setPosition(getVector2fNotCollidingWithEntity(snake));

		std::ostringstream ss;
		ss << "Score: " << score;
		scoreTxt.setString(ss.str());

		ss.str("");
		ss.clear();
	}


	return true;
}

void Game::updateEntitiesForMovement(const AppOrientation& orientation)
{
	for (Entity* entity : entities)
	{
		entity->update(orientation);
	}
}


void Game::render()
{
	/* Used only for testing some stuff
	sf::Vector2f pos = snake->getPosition();
	pos.x = pos.x + 10;
	pos.y = pos.y + 10;
	food->move(pos);
	*/
	screen->clear(sf::Color::Black);
	for (Entity* entity : entities)
	{
		entity->draw();
	}

	screen->draw(scoreTxt);
	screen->display();
}


sf::Vector2i Game::getVector2fNotCollidingWithEntity(Entity* entity) const
{
	const bool locFound = false;
	while (!locFound)
	{
		sf::Vector2i randomPos = getRandomVector2f();
		sf::Vector2i position = getTileTopLeftForPos(randomPos);
		std::cout << "New pos generated " << position.x << ", " << position.y << std::endl;
		if (!entity->collide(position))
			return position;
	}
}

void Game::homeMenuLoop() const
{
	// MainMenu menu(screen);
	MainMenuView menuView(screen);
	menuView.loop();
}

sf::Vector2i Game::getRandomVector2f() const
{
	const int x = random->getRandomInt(0, screen->getSize().x - 1);
	const int y = random->getRandomInt(0, screen->getSize().y - 1);
	return sf::Vector2i(x, y);
}

void Game::resetState()
{
	score = 0;
	scoreTxt.setString("Score: 0");
	if (snake == nullptr)
	{
		snake = new Snake(screen);
		entities.push_back(snake);
	}
	else
	{
		snake->resetState();
		snake->setPosition(getRandomVector2f());
	}

	if (food == nullptr)
	{
		food = new Food(screen, getVector2fNotCollidingWithEntity(snake));
		entities.push_back(food);
	}
	else
		food->setPosition(getVector2fNotCollidingWithEntity(snake));
	screen->clear();
}

void Game::gameLoop()
{
	resetState();

	screen->setFramerateLimit(20);
	while (currentView == GameView::Game)
	{
		if (update())
			render();
	}
}

void Game::gameOverLoop() const
{
	GameOverView gameOverView(screen);
	gameOverView.loop();
}

void Game::setupScene()
{
}

void Game::gameOver()
{
}

void Game::loadResources()
{
	if (!gameFonts[GameView::HomeMenu].loadFromFile(APP_BASE_PATH "resources/fonts/pixel/Pixel NES.otf")
		||
		!gameFonts[GameView::Game].loadFromFile(APP_BASE_PATH "resources/fonts/pixel/Pixel NES.otf")
		||
		!gameFonts[GameView::GameOver].loadFromFile(APP_BASE_PATH "resources/fonts/pixel/Pixel NES.otf"))
	{
	}

	gameFonts[GameView::PauseMenu] = gameFonts[GameView::HomeMenu];
}

void Game::onStartGame()
{
	currentView = GameView::Game;
}

void Game::onExitGame()
{
	currentView = GameView::Exiting;
}

sf::Font& Game::getFont(const GameView& gameView)
{
	if (gameFonts.find(gameView) != gameFonts.end())
		return gameFonts[gameView];
	else
		return gameFonts[GameView::Game]; // default font
}

sf::RectangleShape Game::buildTile(const int xPos, const int yPos, const sf::Color& color)
{
	return buildTile(sf::Vector2i(xPos, yPos), color);
}

sf::Vector2i Game::getTileTopLeftForPos(int xPos, int yPos)
{
	// if we are given xPos = 65 and yPos = 21
	// that should belong to xTileIndex = 3 yTileIndex= 1
	// so we should return x: 60; y = 20
	const int xTileIndex = xPos / TILE_SIZE;
	const int yTileIndex = yPos / TILE_SIZE;

	return sf::Vector2i(xTileIndex * TILE_SIZE, yTileIndex * TILE_SIZE);
}

sf::Vector2i Game::getTileTopLeftForPos(const sf::Vector2i& pos) const
{
	return getTileTopLeftForPos(pos.x, pos.y);
}
