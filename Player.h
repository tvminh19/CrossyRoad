#ifndef _H_CPLAYER_H_
#define _H_CPLAYER_H_
#include <SFML/Graphics.hpp>

class Player{
private:
    sf::RectangleShape shape;
    float time;
    sf::Clock clock;
public:
    void init(){
        this->shape.setSize(sf::Vector2f(50.f, 50.f));
        this->shape.setOutlineColor(sf::Color::Red);
        this->shape.setPosition(sf::Vector2f(540, 660));
    }

    void update(){
        time=clock.restart().asSeconds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            this->left();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            this->right();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            this->up();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            this->down();
        }
    }

    void up(){
        this->shape.move(0.f, -5.f);
    }
    void down(){
        this->shape.move(0.f, 5.f);
    }
    void right(){
        this->shape.move(5.f, 0.f);
    }
    void left(){
        this->shape.move(-5.f, 0.f);
    }

    void render(sf::RenderWindow& window){
        window.draw(this->shape);
    }
};




#endif