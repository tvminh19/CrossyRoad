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

    bool isPause=false;

    bool win=false;
public:

    //constructor & Destructor
    Game(){
        this->initVars();
    }

    ~Game(){
        delete player;
        delete trafficlane;
    }

    void update(sf::RenderWindow& window){
        this->pollEvents(window);

        this->player->update(window);

        this->trafficlane->update(window, level);
    }

    void render(sf::RenderWindow& window){
        window.clear();

        this->player->render(window);

        this->trafficlane->renderEnemies(window);

        window.display();
    }

    bool isWin(){
        if (this->player->getShape().getPosition().y==10){
            level++;
            this->win=true;
            return true;
        }
        return false;
    }

    void pollEvents(sf::RenderWindow& window){
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
    
    int runGame(sf::RenderWindow& window){
        while(window.isOpen()){
            if (!win)
                this->update(window);
            this->render(window);

            //win
            if (isWin()){
                window.clear(sf::Color::Black);
                this->drawWin(window);
                sf::Clock clock;
                int t=3;
                clock.restart().asSeconds();
                while (1){
                    if (clock.getElapsedTime()>sf::seconds(t)){
                        win=false;
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
                int k=this->drawSubMenu(window);
                if (k==0){
                    return this->runGame(window);
                }
                else if (k==1){
                    return 0;
                }
            }

            //lose
            else if (this->trafficlane->checkCollision(this->player->getShape().getGlobalBounds())){
               int k=this->drawLoseMenu(window);
                if (k==0){
                    this->setLevel(1);
                    return this->runGame(window);
                }
                else if (k==1){
                    return 0;
                }
            }
        }
        return 999;
    }

    //set & get level
    void setLevel(int _level){
        level=_level;
    }

    int getLevel(){
        return this->level;
    }

    void drawWin(sf::RenderWindow& window){
        sf::Text text;
        sf::Font font;
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setString("Next Level:" + std::to_string(level));
        text.setFillColor(sf::Color::Cyan);
        text.setCharacterSize(60);
        text.setPosition(350,300);
        text.setStyle(sf::Text::Bold);

        window.draw(text);
        window.display();
    }

/* -------------------------------------------------------------------------- */
/*                                   border                                   */
/* -------------------------------------------------------------------------- */
    int drawSubMenu(sf::RenderWindow& window){
		window.clear();
		std::string menu[2]={"Resume", "Exit"};
		sf::Text text[2];
		sf::Font font;
		font.loadFromFile("arial.ttf");

		//setup for line
		for (int i=0; i<2; ++i){
			text[i].setFont(font);
			text[i].setCharacterSize(40);
			text[i].setPosition(sf::Vector2f(window.getSize().x / 2 - 75, i * 62 + 350));
			text[i].setFillColor(sf::Color::Cyan);
			text[i].setString(menu[i]);
		}
		text[0].setFillColor(sf::Color::Red);
		
		int pos=0;

		// for (int i=0; i<5; ++i){
		// 	window.draw(text[i]);
		// 

		sf::Clock clock;
		sf::Time time=sf::seconds(0.15f);
		clock.restart().asSeconds();
		while (window.isOpen()){
			this->pollEvents(window);
			for (int i=0; i<2; ++i){
				window.draw(text[i]);
			}

			window.display();

			if (clock.getElapsedTime()>=time){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && pos>0){
					text[pos].setFillColor(sf::Color::Cyan);
					pos--;
					text[pos].setFillColor(sf::Color::Red);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos<1){
					text[pos].setFillColor(sf::Color::Cyan);
					pos++;
					text[pos].setFillColor(sf::Color::Red);
				}
				clock.restart().asSeconds();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
				return pos;
			}
		}
		return 1;
	}

	int drawLoseMenu(sf::RenderWindow& window){
		window.clear();
		std::string menu[2]={"Yes", "No"};
		sf::Text text[2];
		sf::Font font;
		font.loadFromFile("arial.ttf");

		//setup for line
		for (int i=0; i<2; ++i){
			text[i].setFont(font);
			text[i].setCharacterSize(40);
			text[i].setPosition(sf::Vector2f(window.getSize().x / 2 - 75, i * 62 + 350));
			text[i].setFillColor(sf::Color::Cyan);
			text[i].setString(menu[i]);
		}
		text[0].setFillColor(sf::Color::Red);
		
		int pos=0;

		// for (int i=0; i<5; ++i){
		// 	window.draw(text[i]);
		// 

		sf::Clock clock;
		sf::Time time=sf::seconds(0.15f);
		clock.restart().asSeconds();
		while (window.isOpen()){
			this->pollEvents(window);
			for (int i=0; i<2; ++i){
				window.draw(text[i]);
			}

			window.display();

			if (clock.getElapsedTime()>=time){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && pos>0){
					text[pos].setFillColor(sf::Color::Cyan);
					pos--;
					text[pos].setFillColor(sf::Color::Red);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos<1){
					text[pos].setFillColor(sf::Color::Cyan);
					pos++;
					text[pos].setFillColor(sf::Color::Red);
				}
				clock.restart().asSeconds();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
				return pos;
			}
		}
		return 1;
	}
};



#endif