#include "Bird.h"


Bird::Bird() {
    // this->shape.setPosition(50.0f, 50.0f);
    this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
    // this->shape.setFillColor(sf::Color::Cyan);
}

void Bird::update() {
    time=clock.restart().asSeconds();
    this->shape.move(speed.x, speed.y);
    this->texture.loadFromFile("bird.png");
    this->shape.setTexture(&texture);
    this->texture.setSmooth(true);
}

