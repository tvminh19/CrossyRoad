#ifndef _CGAME_H_
#define _CGAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "TrafficLane.h"

class Game{
private:
    //prepare for making window
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event event;
    
    TrafficLane trafficlane;
    Player player;

    bool isRunning;

    void initVars(){
        this->player.init();
        this->isRunning=false;
    }

    void initWindow(){
        this->videoMode.height=720;
        this->videoMode.width=1080;

        this->window=new sf::RenderWindow(
            this->videoMode,
            "Crossy Road",
            sf::Style::Default
        );

        this->window->setFramerateLimit(60);
    }

public:

    //constructor & Destructor
    Game(){
        this->initVars();
        this->initWindow();
    }

    void update(){
        this->pollEvents();

        this->player.update();

        this->trafficlane.update(*window);
    }

    void render(){
        this->window->clear();

        this->player.render(*window);

        this->trafficlane.renderEnemies(*window);

        this->window->display();
    }

    ~Game(){
        delete window;
    }

    void pollEvents(){
        while (this->window->pollEvent(this->event))
        {
            switch (this->event.type)
            {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event.key.code == sf::Keyboard::Escape)
                    this->window->close();
                if (this->event.key.code == sf::Keyboard::P)
                    this->isRunning = true;
                break;
            }
        }
    }
    
    void runGame(){
       while(this->window->isOpen()){
           this->update();
           this->render();
       }
    }

};



#endif