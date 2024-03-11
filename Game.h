#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <iostream>

class Game {
private:
	sf::RenderWindow window;

	sf::RectangleShape screenShape;
	sf::Texture screenImage;

	sf::RectangleShape bgShape;
	sf::Texture bgImage;

	std::vector<Button> buttons;

	int WolfPosition = 0; // 0 - LU, 1 - LD, 2 - RU, 3 - RD

public:
	Game();
	void run();

private:
	void processEvents();
	void update();
	void render();
};