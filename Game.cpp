#include "Game.h"
#include <Windows.h>

Game::Game()
	: window(sf::VideoMode(1200, 690), "Nu Pogodi!"),
	th(incrementer)
{
	bgImage.loadFromFile("./image/bg.png");
	bgShape.setSize(sf::Vector2f(1200, 690));
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

	eggImage.loadFromFile("./image/egg.png");

	int posEggs[24][3] = {  {330, 265, 20},
							{370, 275, 80},
							{400, 300, 140},
							{420, 325, 180},
							{440, 350, 220},
							{450, 510, 200}, // ”пало

							{330, 365, 20},
							{370, 375, 80},
							{400, 400, 140},
							{420, 425, 180},
							{440, 450, 220},
							{450, 510, 200}, // ”пало

							{870, 293, 200},
							{854, 290, 140},
							{820, 288, 80},
							{780, 302, 20},
							{745, 345, -40},
							{765, 510, 200}, // ”пало

							{870, 393, 200},
							{854, 390, 140},
							{820, 388, 80},
							{780, 402, 20},
							{745, 445, -40},
							{765, 510, 200}, // ”пало
	};

	for (int i = 0; i < 24; i++) {
		sf::RectangleShape shape;

		shape.setSize(sf::Vector2f(26, 19));
		shape.setTexture(&eggImage);
		shape.setPosition(sf::Vector2f(posEggs[i][0], posEggs[i][1]));
		shape.rotate(posEggs[i][2]);

		eggShapes.push_back(shape);
	}
}


Game::~Game() {
	th.join();
}


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

	if (value % speed == 0) {
		spawnCount++;
		moveEggs();
		if (spawnCount >= spawnRate) {
			spawnCount = 0;
			createRandomEgg();
		}
		//showInfoByEggs();
	}
}


void Game::render() {
	window.clear();
	window.draw(bgShape);
	window.draw(screenShape);

	for (auto el : buttons) {
		window.draw(el.getShape());
	}

	for (int i = 0, count = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (eggStatus[i][j]) {
				window.draw(eggShapes[count]);
			}
			count++;
		}
	}

	/*for (auto egg : eggShapes) {
		window.draw(egg);
	}*/

	window.display();
}


void Game::createRandomEgg() {
	eggStatus[rand() % 4][0] = true;
}


void Game::showInfoByEggs() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			cout << eggStatus[i][j] << " ";
		}
		cout << " : ";
	}
	cout << endl;
}


void Game::moveEggs() {
	for (int i = 0; i < 4; i++) {
		for (int j = 6; j > 0; j--) {
			swap(eggStatus[i][j], eggStatus[i][j - 1]);
		}
	}
}


void Game::incrementer() {
	while (true) {
		this_thread::sleep_for(chrono::milliseconds(100));
		value++;
		//cout << value << endl;
	}
}


void Game::run() {
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

int Game::value = 0;