#include "Game.h"

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left 
			|| event.type == sf::Event::MouseButtonReleased) {
			sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
			int count = 0;

			for (auto& el : buttons) {
				if (el.getShape().getGlobalBounds().contains(float(mousePosition.x), float(mousePosition.y))) {
					el.changeStatus();
					WolfPosition = count;
				}
				count++;
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			buttons[0].changeStatus();
			WolfPosition = 0;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			buttons[1].changeStatus();
			WolfPosition = 1;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
			buttons[2].changeStatus();
			WolfPosition = 2;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
			buttons[3].changeStatus();
			WolfPosition = 3;
		}
	}
}

void Game::update() {
	switch (WolfPosition) {
	case 0:
		screenImage.loadFromFile("./image/LU.png");
		screenShape.setTexture(&screenImage);
		break;

	case 1:
		screenImage.loadFromFile("./image/LD.png");
		screenShape.setTexture(&screenImage);
		break;

	case 2:
		screenImage.loadFromFile("./image/RU.png");
		screenShape.setTexture(&screenImage);
		break;

	case 3:
		screenImage.loadFromFile("./image/RD.png");
		screenShape.setTexture(&screenImage);
		break;
	}
}

void Game::render() {
	window.clear();
	window.draw(bgShape);
	window.draw(screenShape);

	for (auto el : buttons) {
		window.draw(el.getShape());
	}

	window.display();
}

Game::Game()
	: window(sf::VideoMode(1200, 690), "Nu Pogodi!")
{
	bgShape.setSize(sf::Vector2f(1200, 690));
	bgImage.loadFromFile("./image/bg.png");
	bgShape.setTexture(&bgImage);

	screenImage.loadFromFile("./image/LU.png");
	screenShape.setSize(sf::Vector2f(637, 410));
	screenShape.setPosition(sf::Vector2f(280, 138));
	screenShape.setTexture(&screenImage);

	sf::Vector2f pos1(95, 440);
	sf::Vector2f pos2(95, 565);
	sf::Vector2f pos3(1045, 440);
	sf::Vector2f pos4(1045, 565);

	buttons.push_back(Button(pos1));
	buttons.push_back(Button(pos2)); 
	buttons.push_back(Button(pos3)); 
	buttons.push_back(Button(pos4));
}

void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}
