#include "Dinasour.h"


Dinasour::Dinasour() {
    this->shape.setPosition(50.0f, 50.0f);
    this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
    // this->shape.setFillColor(sf::Color::Magenta);
    this->texture.loadFromFile("src/dinasour.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
    sound.openFromFile("sound/dinosaur.ogg");
}