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

	int posEggs[24][3] = { {330, 265, 20},
							{370, 275, 80},
							{400, 300, 140},
							{420, 325, 180},
							{440, 350, 220},
							{450, 510, 200}, // Óïàëî

							{330, 365, 20},
							{370, 375, 80},
							{400, 400, 140},
							{420, 425, 180},
							{440, 450, 220},
							{450, 510, 200}, // Óïàëî

							{870, 293, 200},
							{854, 290, 140},
							{820, 288, 80},
							{780, 302, 20},
							{745, 345, -40},
							{765, 510, 200}, // Óïàëî

							{870, 393, 200},
							{854, 390, 140},
							{820, 388, 80},
							{780, 402, 20},
							{745, 445, -40},
							{765, 510, 200}, // Óïàëî
	};

	for (int i = 0; i < 24; i++) {
		sf::RectangleShape shape;

		shape.setSize(sf::Vector2f(26, 19));
		shape.setTexture(&eggImage);
		shape.setPosition(sf::Vector2f(posEggs[i][0], posEggs[i][1]));
		shape.rotate(posEggs[i][2]);

		eggShapes.push_back(shape);
	}

	font.loadFromFile("./font/Segment7Standard.otf");
	score.setFont(font);
	score.setPosition(sf::Vector2f(650, 150));
	score.setFillColor(sf::Color::Black);
	score.setCharacterSize(70);

	bunny.setSize(sf::Vector2f(605, 340));
	chickenShape.setSize(sf::Vector2f(605, 440));
	lifeTexture.loadFromFile("./image/mistake.png");

	for (int i = 0; i < 3; i++) {
		sf::RectangleShape shape;
		shape.setTexture(&lifeTexture);
		shape.setPosition(sf::Vector2f(310 + i * 40, 160));
		shape.setSize(sf::Vector2f(605, 340));
		lifes.push_back(shape);
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

	if (value >= speed) {
		spawnCount++;
		moveEggs();
		if (spawnCount >= spawnRate) {
			spawnCount = 0;
			createRandomEgg();
		}
		value = 0;

		if ((countCaughtEggs % (3 * level)) == 0 && countCaughtEggs > 0) {
			if (spawnRate > 1) {
				spawnRate--;
				level++;
				bunnyState = 1;
			}
		}

		if ((countCaughtEggs % (20 * level)) == 0 && countCaughtEggs > 0) {
			bunnyState = 1;
			if (speed > 4) speed--; 
		}

		if (bunnyState != 0 && ticks < 3) {
			if (value % 5 == 0) bunnyAnimation(); 
			ticks++;
		}

		else {
			bunnyState = 0;
			ticks = 0;
		}
	}

	score.setString(to_string(countCaughtEggs));
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
	window.draw(score);

	for (int i = 0; i < mistakes; i++) {
		window.draw(lifes[i]);
	}

	if (statusChickenAnimation != 0) {
		while (statusChickenAnimation < 5) {
			chickenAnimation();
			statusChickenAnimation++;

			window.clear();
			window.draw(bgShape);
			window.draw(screenShape);
			window.draw(chickenShape);
			for (int i = 0; i < mistakes; i++) {
				window.draw(lifes[i]);
			}
			window.draw(score);
			window.display();

			Sleep(500);
		}
		statusChickenAnimation = 0;
	}

	if (bunnyState != 0) window.draw(bunny);

	if (mistakes == 3) {
		gameOver();
	}

	else window.display();
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

void Game::reset() {
	int level = 1;
	int speed = 10;
	int spawnRate = 5;
	int spawnCount = 0;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			eggStatus[i][j] = 0;
		}
	}
}

void Game::chickenAnimation() {
	string path = "";
	if (failSide < 2) {
		path = "./image/chickenl" + to_string(statusChickenAnimation) + ".png";
		chickenShape.setPosition(sf::Vector2f(270, 138));
	}
	else {
		path = "./image/chickenr" + to_string(statusChickenAnimation) + ".png";
		chickenShape.setPosition(sf::Vector2f(380, 138));
	}
	chickenTexture.loadFromFile(path);
	chickenShape.setTexture(&chickenTexture);
}

void Game::gameOver() {
	reset();
	mistakes = 0;
	countCaughtEggs = 0;
	value = 0;
}

void Game::bunnyAnimation() {
	bunny.setPosition(sf::Vector2f(255, 180));
	bunnyState++;
	if (bunnyState > 2) bunnyState = 1;

	string path = "./Image/lvlup" + to_string(bunnyState) + ".png";
	bunnyTexture.loadFromFile(path);
	bunny.setTexture(&bunnyTexture);
}

void Game::moveEggs() {
	for (int i = 0; i < 4; i++) {
		for (int j = 5; j > 0; j--) {
			swap(eggStatus[i][j], eggStatus[i][j - 1]);
			if (j == 5 && eggStatus[i][j] == 1) {
				if (i == WolfPosition) {
					eggStatus[i][j] = 0;
					countCaughtEggs++;
				}
			}
			if (j == 5) {
				if (eggStatus[i][j] == 1) {
					mistakes++;
					failSide = i;
					statusChickenAnimation = 1;
					reset();
				}
			}
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