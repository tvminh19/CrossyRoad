#include "Car.h"

public: Car::Car() {
    this->shape.setSize(sf::Vector2f(200.0f, 100.0f));
    this->texture.loadFromFile("car.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
    // this->shape.setFillColor(sf::Color::Red);
}

void Car::update() {
    time=clock.restart().asSeconds();
    this->shape.move(speed.x, speed.y);
}
