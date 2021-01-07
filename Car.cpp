#include "Car.h"

Car::Car() {
    this->shape.setSize(sf::Vector2f(200.0f, 100.0f));
    this->texture.loadFromFile("car.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
    // this->shape.setFillColor(sf::Color::Red);
    sound.openFromFile("car.ogg");
}

void Car::update() {
    time=clock.restart().asSeconds();
    this->shape.move(speed.x, speed.y);
}

void Car::makeSound()
{
    sound.play();
    sf::sleep(sf::seconds(3));
}