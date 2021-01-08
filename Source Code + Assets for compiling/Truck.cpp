#include "Truck.h"


Truck::Truck() {
    // this->shape.setPosition(50.0f, 50.0f);
    this->shape.setSize(sf::Vector2f(200.0f, 100.0f));
    // this->shape.setFillColor(sf::Color::Green);
    this->texture.loadFromFile("src/Truck.png");
    this->texture.setSmooth(true);
    this->shape.setTexture(&texture);
    sound.openFromFile("sound/truck.ogg");
}