#pragma once
#include <SFML/Graphics.hpp>
#include "entities/Snake.h"
#include "entities/Food.h"

class Game;
class Random;

extern Game* game;

enum class GameView
{
	HomeMenu,
	Game,
	PauseMenu,
	GameOver,
	Exiting
};

class Game
{
public:
	Game(int argc, char** argv);
	~Game();

	void start();
	void onStartGame();
	void onExitGame();

	sf::Font& getFont(const GameView& gameView);

	static sf::RectangleShape buildTile(const int xPos, const int yPos, const sf::Color& color);
	static sf::RectangleShape buildTile(const sf::Vector2i& loc, const sf::Color& color);
	static sf::Vector2i getTileTopLeftForPos(int xPos, int yPos);

private:
	void updateEntitiesForMovement(const AppOrientation& orientation);
	bool update();

	void render();
	sf::Vector2i getTileTopLeftForPos(const sf::Vector2i& pos) const;
	sf::Vector2i getVector2fNotCollidingWithEntity(Entity* entity) const;
	void homeMenuLoop() const;
	sf::Vector2i getRandomVector2f() const;
	void resetState();
	void gameLoop();
	void gameOverLoop() const;
	void startLoop();
	void setupScene();
	void gameOver();
	void loadResources();

private:
	Snake* snake;
	sf::RenderWindow* screen;
	float scale;
	int score;

	std::map<GameView, sf::Font> gameFonts;

	Food* food;

	std::vector<Entity*> entities;
	Random* random;

	GameView currentView;
	sf::Text scoreTxt;
	sf::Font mainFont;
	int scoreStep;
};
