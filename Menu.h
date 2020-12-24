#ifndef _MENU_H_
#define _MENU_H_

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Menu{
private:
	sf::RenderWindow* window=nullptr;
	sf::Event event;
	sf::VideoMode videoMode;
	Game* game=nullptr;

	void initWindow(){
		this->videoMode.height=720;
		this->videoMode.width=1080;
		window=new sf::RenderWindow(
			this->videoMode,
			"Crossy Road",
			sf::Style::Default
		);
		this->window->setFramerateLimit(60);
	}
public:
	//cons & des
	Menu(){
		//initWindow
		this->game=new Game;
		this->initWindow();
	}
	
	~Menu(){
		delete window;
		delete game;
	}

	/**
	 * draw the menu
	 * return the choices
	 * 0 -> newGame
	 * 1 -> loadGame
	 * 2 -> Ranking
	 * 3 -> Music
	 * 4 -> Exit
	 */
	int drawMenu(){
		window->clear();
		std::string menu[5]={"New Game", "Loading Game", "Ranking", "Music: ON", "Exit"};
		sf::Text text[5];
		sf::Font font;
		font.loadFromFile("arial.ttf");

		//setup for line
		for (int i=0; i<5; ++i){
			text[i].setFont(font);
			text[i].setCharacterSize(40);
			text[i].setPosition(sf::Vector2f(this->window->getSize().x / 2 - 75, i * 62 + 350));
			text[i].setFillColor(sf::Color::Cyan);
			text[i].setString(menu[i]);
		}
		text[0].setFillColor(sf::Color::Red);
		
		int pos=0;

		// for (int i=0; i<5; ++i){
		// 	window->draw(text[i]);
		// 

		sf::Clock clock;
		sf::Time time=sf::seconds(0.15f);
		clock.restart().asSeconds();
		while (window->isOpen()){
			this->pollEvents();
			for (int i=0; i<5; ++i){
				window->draw(text[i]);
			}

			window->display();

			if (clock.getElapsedTime()>=time){
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && pos>0){
					text[pos].setFillColor(sf::Color::Cyan);
					pos--;
					text[pos].setFillColor(sf::Color::Red);
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos<4){
					text[pos].setFillColor(sf::Color::Cyan);
					pos++;
					text[pos].setFillColor(sf::Color::Red);
				}
				clock.restart().asSeconds();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
				if (pos==0){
					return this->newGame();
				}
				if (pos==1){
					return this->loadGame();
				}
				if (pos==2){
					return this->rank();
				}
				if (pos==3){
					return this->music();
				}
				if (pos==4){
					return this->exit();
				}
			}
		}
		return 4;
	}

	int newGame(){
		if (this->game->runGame(*window)==0){
			return this->drawMenu();
		}
	}

	void saveGame(){

	}

	int loadGame(){
		std::cout<<"loadgame.\n";
		return 0;
	}

	int rank(){
		std::cout<<"rank.\n";
		return 0;
	}

	int music(){
		std::cout<<"music.\n";
		return 0;
	}

	int exit(){
		std::cout<<"exit.\n";
		return 0;
	}

	sf::RenderWindow* getWindow(){
		return this->window;
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
				break;
            }
        }
    }
};

#endif // DEBUG