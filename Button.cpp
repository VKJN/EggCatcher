#include "Button.h"

Button::Button(sf::Vector2f position) {
    button.setRadius(28.f);
    button.setFillColor(sf::Color(0, 0, 0, 0));
    button.setPosition(position);
}

void Button::changeStatus() {
    status = !status;
    if (status) {
        button.setFillColor(sf::Color(0, 0, 0, 100));
    }

    else {
        button.setFillColor(sf::Color(0, 0, 0, 0));
    }
}

bool Button::getStatus() {
    return status;
}

sf::CircleShape& Button::getShape() {
    return button;
}

sf::Vector2f Button::getPosition() {
    return button.getPosition();
}