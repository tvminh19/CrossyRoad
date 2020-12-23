#ifndef _CBIRD_H_
#define _CBIRD_H_
#include "Enemy.h"

class Bird: public Enemy{
private:
    //
public:
    Bird(){
        this->shape.setPosition(50.0f, 50.0f);
	    this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
	    this->shape.setFillColor(sf::Color::Cyan);
    }

    void update(){
        time=clock.restart().asSeconds();
        this->shape.move(speed.x, speed.y);
    }

};

#endif