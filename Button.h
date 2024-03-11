#pragma once
#include <SFML/Graphics.hpp>

class Button {
private:
	sf::CircleShape button;
	bool status = false;
public:
	Button(sf::Vector2f position);
	void changeStatus();
	bool getStatus();
	sf::CircleShape& getShape();
	sf::Vector2f getPosition();
};