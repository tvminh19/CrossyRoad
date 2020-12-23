#ifndef _DINASOUR_H_
#define _DINASOUR_H_
#include "Enemy.h"

class Dinasour: public Enemy{
private:
    //
public:
    Dinasour(){
        this->shape.setPosition(50.0f, 50.0f);
	    this->shape.setSize(sf::Vector2f(100.0f, 100.0f));
	    // this->shape.setFillColor(sf::Color::Magenta);
        this->texture.loadFromFile("dinasour.png");
        this->shape.setTexture(&texture);
        this->texture.setSmooth(true);
    }
    
    void update(){
        time=clock.restart().asSeconds();
        this->shape.move(speed.x, speed.y);
    }

};

#endif