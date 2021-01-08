#ifndef _CENEMY_H_
#define _CENEMY_H_
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Enemy{
protected:
    sf::Vector2f speed;
    sf::Music sound;

    sf::RectangleShape shape;
    sf::Texture texture;
    
    float time;
    sf::Clock clock;
    friend class TrafficLane;
public:
    sf::RectangleShape getShape();
    void update();
    
    void setSpeed(float x, float y);

    void makeSound();
};

#endif