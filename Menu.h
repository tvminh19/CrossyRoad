#ifndef CMenu_H
#define CMenu_H
#pragma warning(disable : 4996)


#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Game.h"

#define MENU_CHOICE 5

class Menu {
private:
	sf::RenderWindow* window=nullptr;
	sf::VideoMode videoMode;
	sf::Event event;
	Game game;

	int selected;
	int level = 1;
	bool sound;
	sf::Font font;
	sf::Text menu[MENU_CHOICE];
	sf::Music sound_track;
	
public:
	Menu();
	~Menu();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void LoadGame(sf::RenderWindow& window);
	void set_sound();
	void set_level(const int& lvl = 1);
	void play_sound();
	int get_choice();
	bool get_sound();

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

	sf::RenderWindow* getWindow(){
		return this->window;
	}

	int newGame(){
		this->game.setLevel(1);

		//-1 is lose
		//0 pause game
		int t = this->game.runGame(*window);

		//lose
		if (t==-1){
			//
		}
		//pause game
		else if (t==0){
			// 
		}
	}
};

#endif // !CMenu_H