#ifndef _CGAME_H_
#define _CGAME_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include <iostream>
#include "TrafficLane.h"

class Game{
private:
    //prepare for making window
    sf::Event event;
    
    TrafficLane* trafficlane;
    Player* player;

    bool isRunning;

    void initVars(){
        this->trafficlane=new TrafficLane;
        this->player=new Player;
        this->isRunning=false;
    }

    int level=1;

    bool isPause = false;

    bool win = false;
public:

    //constructor & Destructor
    Game();

    ~Game();

    void update(sf::RenderWindow& window);

    void render(sf::RenderWindow& window);

    bool isWin();

    void pollEvents(sf::RenderWindow& window);
    
    int runGame(sf::RenderWindow& window);

    //set & get level
    void setLevel(const int& _level);

    int getLevel();

    void drawWin(sf::RenderWindow& window);

};

#endif