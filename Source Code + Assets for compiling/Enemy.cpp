#include "Enemy.h"


sf::RectangleShape Enemy::getShape() {
    return this->shape;
}

void Enemy::setSpeed(float x, float y) {
    speed.x=x;
    speed.y=y;
}

