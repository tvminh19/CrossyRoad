#ifndef _TRUCK_H_
#define _TRUCK_H_
#include "Enemy.h"

class Truck: public Enemy{
private:
    //
public:
    Truck(){
        this->shape.setPosition(50.0f, 50.0f);
	    this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
	    this->shape.setFillColor(sf::Color::Green);
    }

    void update(){
        time=clock.restart().asSeconds();
        this->shape.move(3.f,0.f);
    }

};

#endif