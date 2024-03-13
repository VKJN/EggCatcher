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

	vector<sf::RectangleShape> eggShapes;
	sf::Texture eggImage;

	std::vector<Button> buttons;

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
};