#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_
#include <SFML/Graphics.hpp>

class TrafficLight{
private:
    sf::RectangleShape shape;
public:
    TrafficLight(){
        shape.setSize(sf::Vector2f(50.f,50.f));
        shape.setFillColor(sf::Color::Red);
    }


    //change color
    void update(bool canMove){
        if (canMove && shape.getFillColor()==sf::Color::Green){
            shape.setFillColor(sf::Color::Red);
        }
        else if (!canMove && shape.getFillColor()==sf::Color::Red){
            shape.setFillColor(sf::Color::Green);
        }
    }

    void render(sf::RenderWindow& window){
        window.draw(shape);
    }

    void setPosition(float x, float y){
        this->shape.setPosition(sf::Vector2f(x,y));
    }

    sf::RectangleShape getShape(){
        return this->shape;
    }

};

#endif // !_TRAFFIC_LIGHT_H_
