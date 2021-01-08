#include "Car.h"

Car::Car() {
    this->shape.setSize(sf::Vector2f(200.0f, 100.0f));
    this->texture.loadFromFile("src/car.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
    // this->shape.setFillColor(sf::Color::Red);
    sound.openFromFile("sound/car.ogg");
}