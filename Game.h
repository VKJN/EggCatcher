#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

class Game {
private:
	sf::RenderWindow window;

	sf::RectangleShape screenShape;
	sf::Texture screenImage;

	sf::RectangleShape bgShape;
	sf::Texture bgImage;

	std::vector<Button> buttons;

	vector<sf::RectangleShape> eggShapes;
	sf::Texture eggImage;

	sf::RectangleShape chickenShape;
	sf::Texture chickenTexture;
	int statusChickenAnimation; // 0 - none  1-4 - animation 
	int failSide = 0;

	vector<sf::RectangleShape> lifes;
	sf::Texture lifeTexture;

	sf::RectangleShape bunny;
	sf::Texture bunnyTexture;
	int bunnyState = 0;
	int ticks = 0;

	sf::Text score;
	sf::Font font;

	int WolfPosition = 3; // 0 - LU, 1 - LD, 2 - RU, 3 - RD

	int level = 1;
	int speed = 10;
	int spawnRate = 5;
	int spawnCount = 0;

	int mistakes = 0;
	bool eggStatus[4][6]{};
	int countCaughtEggs = 0;

	static int value;
	thread th;
	void static incrementer();

public:
	Game();
	~Game();
	void run();

private:
	void processEvents();
	void update();
	void render();
	void createRandomEgg();;
	void moveEggs();
	void showInfoByEggs();
	void reset();
	void chickenAnimation();
	void gameOver();
	void bunnyAnimation();
};