#ifndef _CENEMY_H_
#define _CENEMY_H_
#include <SFML/Graphics.hpp>

class Enemy{
protected:
    sf::Vector2f speed;
public:
    sf::RectangleShape shape;
    float time;
    sf::Clock clock;

    sf::RectangleShape getShape(){
        return this->shape;
    }

    virtual void update()=0;
    
    void setSpeed(float x, float y){
        speed.x=x;
        speed.y=y;
    }
};

#endif