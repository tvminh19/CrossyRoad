#ifndef _H_CPLAYER_H_
#define _H_CPLAYER_H_
#include <SFML/Graphics.hpp>

class Player{
private:
    sf::RectangleShape shape;
    sf::Time time=sf::seconds(0.05f);
    sf::Clock clock;
public:
    void init(){
        this->shape.setSize(sf::Vector2f(50.f, 50.f));
        // this->shape.setOutlineColor(sf::Color::Red);
        this->shape.setFillColor(sf::Color::White);
        this->shape.setPosition(sf::Vector2f(540, 660));
    }

    void update(){
        // time=clock.restart().asSeconds();
        if (this->clock.getElapsedTime()>time){
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
            clock.restart();
        }
    }

    void up(){
        // this->shape.move(0.f, -5.f);
        this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(0, -50));
    }
    void down(){
        // this->shape.move(0.f, 5.f);
        this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(0, 50));
    }
    void right(){
        // this->shape.move(5.f, 0.f);
        this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(50, 0));
    }
    void left(){
        // this->shape.move(-5.f, 0.f);
        this->shape.setPosition(this->shape.getPosition()+sf::Vector2f(-50, 0));
    }

    void render(sf::RenderWindow& window){
        window.draw(this->shape);
    }
};




#endif