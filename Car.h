#ifndef _CAR_H_
#define _CAR_H_
#include "Enemy.h"

class Car: public Enemy{
private:
    
public:
    Car(){
        this->shape.setPosition(50.0f, 50.0f);
	    this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
	    this->shape.setFillColor(sf::Color::Red);
    }

    void update(){
        time=clock.restart().asSeconds();
        this->shape.move(speed.x, speed.y);
    }

};

#endif