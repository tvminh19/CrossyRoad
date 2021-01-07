#ifndef _H_CPLAYER_H_
#define _H_CPLAYER_H_
#include <SFML/Graphics.hpp>

class Player{
private:
    sf::RectangleShape shape;
    sf::Texture texture;
    sf::Time time=sf::seconds(0.05f);
    sf::Clock clock;
public:
    Player();

    void init();

    void update(sf::RenderWindow& window);

    void up();

    void down();

    void right();

    void left();

    void render(sf::RenderWindow& window);

    bool canMove(sf::RenderWindow& window, sf::Vector2f trans);

    sf::RectangleShape getShape();

    void reset();
};




#endif