#include "TrafficLight.h"


TrafficLight::TrafficLight() {
    shape.setSize(sf::Vector2f(50.f,50.f));
    shape.setFillColor(sf::Color::Red);
}

void TrafficLight::update(bool canMove) {
    if (canMove && shape.getFillColor()==sf::Color::Green){
        shape.setFillColor(sf::Color::Red);
    }
    else if (!canMove && shape.getFillColor()==sf::Color::Red){
        shape.setFillColor(sf::Color::Green);
    }
}

void TrafficLight::render(sf::RenderWindow& window) {
    window.draw(shape);
}

void TrafficLight::setPosition(float x, float y) {
    this->shape.setPosition(sf::Vector2f(x,y));
}

sf::RectangleShape TrafficLight::getShape() {
    return this->shape;
}





