#ifndef _CENEMY_H_
#define _CENEMY_H_
#include <SFML/Graphics.hpp>

class Enemy{
protected:
    sf::Vector2f speed;
public:
    sf::Sprite sprite;
    sf::RectangleShape shape;
    sf::Texture texture;
    
    float time;
    sf::Clock clock;

    sf::RectangleShape getShape();
    virtual void update()=0;
    
    void setSpeed(float x, float y);
};

#endif