#ifndef _MENU_H_
#define _MENU_H_

#pragma warning(disable : 4996)

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


class Button {
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Color bgColor;
public:
	Button() {}

	Button(const std::string& t, sf::Vector2f size, int charSize, sf::Color background, sf::Color textColor)
	{
		sf::String str(t);
		text.setString(str);
		text.setColor(textColor);
		text.setCharacterSize(charSize);
		button.setSize(size);
		button.setFillColor(background);
		bgColor = background;
	}

	void set_font(const sf::Font& font)
	{
		text.setFont(font);
	}

	void set_position(sf::Vector2f pos)
	{
		button.setPosition(pos);
		float x = (pos.x + button.getLocalBounds().width / 3) - (text.getLocalBounds().width / 2) - 40;
		float y = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 2) - 15;
		text.setPosition(sf::Vector2f(x, y));
	}

	void drawto(sf::RenderWindow& window)
	{
		window.draw(button);
		window.draw(text);
	}

	bool isMouse(sf::RenderWindow& window)
	{
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;
		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;
		float btnPosWidth = btnPosX + button.getLocalBounds().width;
		float btnPosHeight = btnPosY + button.getLocalBounds().height;

		if (mouseX < btnPosWidth && mouseX > btnPosX && mouseY < btnPosHeight && mouseY > btnPosY)
		{
			button.setFillColor(sf::Color::Yellow);
			return true;
		}
		button.setFillColor(bgColor);
		return false;
	}
	~Button() {}
};

class Menu{
private:
	sf::RenderWindow* window=nullptr;
	sf::Event* event=nullptr;
	sf::VideoMode videoMode;
	Game* game=nullptr;

	void initWindow(){
		this->videoMode.height=720;
		this->videoMode.width=1080;
		window = new sf::RenderWindow(
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
		this->event=new sf::Event;
		this->initWindow();
	}
	
	~Menu(){
		delete window;
		delete game;
		delete event;
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

		std::string menu[5] = {"New Game", "Load Game", "Ranking", "Music: ON", "Exit"};
		std::vector <Button> menu_button;
		sf::Font font;
		sf::Texture texture;

		texture.loadFromFile("logo.png");

		sf::Sprite sprite(texture);
		int i;
		
		font.loadFromFile("Animated.ttf");
		sprite.setPosition(sf::Vector2f(360, 10));
		

		for (i = 0; i < 5; ++i) {
			Button a(menu[i], { 220, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
			a.set_position({ (float)420 , (float)i * 60 + 350 });
			a.set_font(font);
			menu_button.push_back(a);
		}
		
		while (window->isOpen()){
			this->pollEvents();
			for (i = 0; i < 5; ++i){
				menu_button[i].drawto(*window);
			}

			window->draw(sprite);

			window->display();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (i = 0; i < 5; ++i) {
					if (menu_button[i].isMouse(*window))
						return i;
				}
			}

			for (i = 0; i < 5; ++i) {
				menu_button[i].isMouse(*window);
			}

			window->clear();
		}

		return 4;
	}

	int newGame(){
		int t = this->game->runGame(*window);
		delete game;
		game=nullptr;
		game=new Game;
		window->clear(sf::Color::Black);
		window->display();
		if (t==0){
			int k = this->drawSubMenu();
			if (k==0){
				return this->newGame();
			}
			else if (k==1){
				switch (this->drawMenu()){
				case 0:
					return newGame();
					break;
				case 1:
					return loadGame();
					break;
				case 2:
					return rank();
					break;
				case 4:
					return music();
					break;
				case 5:
					return exit();
					break;
				}
			}
		}
		else if (t==-1){
			int k = drawLoseMenu();
			if (k==0){
				return this->newGame();
			}
			else if (k==1){
				switch (this->drawMenu()){
				case 0:
					return newGame();
					break;
				case 1:
					return loadGame();
					break;
				case 2:
					return rank();
					break;
				case 4:
					return music();
					break;
				case 5:
					return exit();
					break;
				}
			}
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
        while (this->window->pollEvent(*this->event))
        {
            switch (this->event->type)
            {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->event->key.code == sf::Keyboard::Escape)
                    this->window->close();
				break;
            }
        }
    }

	int drawSubMenu(){
		window->clear();
		std::string menu[2]={"Resume", "Exit"};
		sf::Text text[2];
		std::vector <Button> menu_button;
		sf::Font font;
		sf::Texture texture;

		texture.loadFromFile("logo.png");

		sf::Sprite sprite(texture);
		int i;

		font.loadFromFile("Animated.ttf");
		sprite.setPosition(sf::Vector2f(190, 100));


		for (i = 0; i < 2; ++i) {
			Button a(menu[i], { 220, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
			a.set_position(sf::Vector2f(window->getSize().x / 2 + 140, i * 65 + 250));
			a.set_font(font);
			menu_button.push_back(a);
		}

		while (window->isOpen()){
			this->pollEvents();
			for (i = 0; i < 2; ++i){
				menu_button[i].drawto(*window);
			}

			window->draw(sprite);
			window->display();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (i = 0; i < 2; ++i) {
					if (menu_button[i].isMouse(*window))
						return i;
				}
			}

			for (i = 0; i < 2; ++i) {
				menu_button[i].isMouse(*window);
			}

			window->clear();
		}
		return 1;
	}

	int drawLoseMenu(){

		window->clear();

		std::string menu[2]={"Try again", "Quit"};
		sf::Text text[2];
		std::vector <Button> menu_button;
		sf::Font font;
		sf::Texture texture;

		texture.loadFromFile("crashed.png");

		sf::Sprite sprite(texture);
		int i;

		font.loadFromFile("Animated.ttf");
		sprite.setPosition(sf::Vector2f(110, 150));

		for (i = 0; i < 2; ++i) {
			Button a(menu[i], { 220, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
			a.set_position(sf::Vector2f(window->getSize().x / 2 + 160, i * 65 + 250));
			a.set_font(font);
			menu_button.push_back(a);
		}

		while (window->isOpen()){
			this->pollEvents();
			for (i = 0; i < 2; ++i){
				menu_button[i].drawto(*window);
			}

			window->draw(sprite);
			window->display();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (i = 0; i < 2; ++i) {
					if (menu_button[i].isMouse(*window))
						return i;
				}
			}

			for (i = 0; i < 2; ++i) {
				menu_button[i].isMouse(*window);
			}

			window->clear();
			
		}
		return 1;
	}
};




#endif // DEBUG