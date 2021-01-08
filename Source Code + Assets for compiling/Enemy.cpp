#include "Enemy.h"


sf::RectangleShape Enemy::getShape() {
    return this->shape;
}

void Enemy::setSpeed(float x, float y) {
    speed.x=x;
    speed.y=y;
}

void Enemy::update() {
    time = clock.restart().asSeconds();
    this->shape.move(speed.x, speed.y);
}

void Enemy::makeSound()
{
    sound.setLoop(0);
    sound.play();
    sf::sleep(sf::seconds(1.5f));
}