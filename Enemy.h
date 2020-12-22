#ifndef _CENEMY_H_
#define _CENEMY_H_
#include <SFML/Graphics.hpp>

class Enemy{
protected:
    
public:
    sf::RectangleShape shape;
    float time;
    sf::Clock clock;
    float speed;

    sf::RectangleShape getShape(){
        return this->shape;
    }

    virtual void update()=0;
};

#endif