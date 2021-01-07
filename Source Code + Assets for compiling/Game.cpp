#include "Game.h"

Game::Game(){
    level = 1;
    this->initVars();
}

Game::~Game(){
    delete player;
    delete trafficlane;
}

void Game::update(sf::RenderWindow& window){
    //Esc 
    this->pollEvents(window);

    //update start position
    this->player->update(window);

    this->trafficlane->update(window, level);
}

void Game::render(sf::RenderWindow& window){
    window.clear();

    this->player->render(window);

    this->trafficlane->renderEnemies(window);

    this->trafficlane->renderTrafficLight(window);

    window.display();
}

bool Game::isWin(){
    if (this->player->getShape().getPosition().y == 10){
        level++;
        this->win = true;
        return true;
    }
    return false;
}

void Game::pollEvents(sf::RenderWindow& window){
    while (window.pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::KeyPressed:
            if (this->event.key.code == sf::Keyboard::Escape)
                window.close();
            if (this->event.key.code == sf::Keyboard::P)
                this->isPause=true;
            break;
        }
    }
}

int Game::runGame(sf::RenderWindow& window){
    while(window.isOpen()){
        if (!win)
            this->update(window);
        this->render(window);

        //win
        if (isWin()){
            window.clear(sf::Color::Black);
            this->drawWin(window);
            sf::Clock clock;
            int t = 3;
            clock.restart().asSeconds();
            while (1){
                if (clock.getElapsedTime()>sf::seconds(t)){
                    win = false;
                    break;
                }
            }
            window.clear(sf::Color::Black);
            this->player->reset();
            // this->trafficlane->resetClock();
            return this->runGame(window);
        }

        //pause
        else if (this->isPause){
            // int k=this->drawSubMenu(window);
            // if (k==0){
            //     return this->runGame(window);
            // }
            // else if (k==1){
            //     return 0;
            // }
            return 0;
        }

        //lose
        else if (this->trafficlane->checkCollision(this->player->getShape().getGlobalBounds())){
        //    int k=this->drawLoseMenu(window);
        //     if (k==0){
        //         this->setLevel(1);
        //         return this->runGame(window);
        //     }
        //     else if (k==1){
        //         return 0;
        //     }
            return -1;
        }
    }

    return 10;
}

void Game::setLevel(const int& _level){
    level = _level;
}

int Game::getLevel(){
    return this->level;
}

void Game::drawWin(sf::RenderWindow& window){
    sf::Text text;
    sf::Font font;
    font.loadFromFile("src/Animated.ttf");
    text.setFont(font);
    text.setString("Next level: " + std::to_string(level));
    text.setFillColor(sf::Color::Cyan);
    text.setCharacterSize(100);
    text.setPosition(300, 280);
    text.setStyle(sf::Text::Bold);

    window.draw(text);
    window.display();
}