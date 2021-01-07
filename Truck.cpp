#include "Truck.h"


Truck::Truck() {
    // this->shape.setPosition(50.0f, 50.0f);
    this->shape.setSize(sf::Vector2f(200.0f, 100.0f));
    // this->shape.setFillColor(sf::Color::Green);
    this->texture.loadFromFile("Truck.png");
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
    sound.openFromFile("truck.ogg");
}

void Truck::update() {
    time=clock.restart().asSeconds();
    this->shape.move(speed.x, speed.y);
}

void Truck::makeSound()
{
    sound.play();
    sf::sleep(sf::seconds(3.5));
}