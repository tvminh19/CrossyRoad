#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_
#include <SFML/Graphics.hpp>

class TrafficLight{
private:
    sf::RectangleShape shape;
public:
    TrafficLight();


    //change color
    void update(bool canMove);

    void render(sf::RenderWindow& window);

    void setPosition(float x, float y);

    sf::RectangleShape getShape();

};

#endif // !_TRAFFIC_LIGHT_H_
