#ifndef _MENU_H_
#define _MENU_H_

#pragma warning(disable : 4996)

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <fstream>



//class TextBox {
//private:
//	sf::Text textbox;
//	std::ostringstream text;
//	int size;
//
//	void logic(const int& typed)
//	{
//		// ESC && ENTER && DELETE
//		if (typed != 27 && typed != 13 && typed != 8)
//			text << static_cast<char>(typed);
//		else if (typed == 8)
//		{
//			if (text.str().length() > 0)
//			{
//				delete_last_char();
//			}
//		}
//		textbox.setString(text.str() + "$");
//	}
//
//	void delete_last_char()
//	{
//		std::string t = text.str();
//		std::string newT(t);
//		newT.pop_back();
//		
//		text.str("");
//		text << newT;
//
//		textbox.setString(text.str());
//	}
//
//public:
//	TextBox() {}
//	TextBox(const int& font_sz, const sf::Color& color)
//	{
//		textbox.setCharacterSize(font_sz);
//		textbox.setColor(color);
//	}
//
//	void set_font(const sf::Font& font)
//	{
//		textbox.setFont(font);
//	}
//
//	void set_position(const sf::Vector2f& pos)
//	{
//		textbox.setPosition(pos);
//	}
//
//	void set_limit(const int& sz)
//	{
//		size = sz;
//	}
//
//	void drawto(sf::RenderWindow& window)
//	{
//		window.draw(textbox);
//	}
//
//	void input(sf::Event input)
//	{
//		int typed = input.text.unicode;
//		if (typed < 128)
//		{
//			if (text.str().length() <= size)
//				logic(typed);
//			else if (text.str().length() > size && typed == 8)
//				delete_last_char();
//			
//		}
//	}
//};

class Button {
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Color bgColor;
public:
	Button() {}

	Button(const std::string& t, const sf::Vector2f& size, const int& charSize, const sf::Color& background, const sf::Color& textColor)
	{
		text.setString(t);
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

	void set_position(const sf::Vector2f& pos)
	{
		button.setPosition(pos);
		float x = (pos.x + button.getLocalBounds().width / 3) - (text.getLocalBounds().width / 2) - 40;
		float y = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 2) - 15;
		text.setPosition(sf::Vector2f(x, y));
	}

	void set_position_input(const sf::Vector2f& pos)
	{
		button.setPosition(pos);
		float x = (pos.x + button.getLocalBounds().width / 5) - (text.getLocalBounds().width / 2) - 40;
		float y = (pos.y + button.getLocalBounds().height / 5) - (text.getLocalBounds().height / 2) - 15;
		text.setPosition(sf::Vector2f(x, y));
	}

	void set_string(const std::string& t)
	{
		text.setString(t);
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
	bool bg_music;
	sf::Music sound_track;

	void initWindow(){
		this->videoMode.height = 720;
		this->videoMode.width = 1080;
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
		//Background music
		this->bg_music = true;
		this->sound_track.openFromFile("music.ogg"); 
		this->sound_track.setPlayingOffset(sf::seconds(15.f));
		this->sound_track.setVolume(12);
		this->sound_track.setLoop(true);
		play_sound();
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

		sf::Clock clock;
		sf::Time time = sf::seconds(0.06f);
		clock.restart().asSeconds();
		
		while (window->isOpen()){
			this->pollEvents();
			for (i = 0; i < 5; ++i){
				menu_button[i].drawto(*window);
			}

			window->draw(sprite);

			for (i = 0; i < 5; ++i) {
				menu_button[i].isMouse(*window);
			}

			if (clock.getElapsedTime() >= time) {
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					for (i = 0; i < 5; ++i) {
						if (menu_button[i].isMouse(*window))
						{
							if (i == 3)
								menu_button[i].set_string(set_sound());
							else
								return i;
						}
					}
				}
				clock.restart().asSeconds();
			}

			window->display();

			window->clear();
		}

		return 4;
	}

	int newGame(const int& level = 1){
		this->game->setLevel(level);
		int t = this->game->runGame(*window);
		int lvl = this->game->getLevel();
		delete game;
		game = new Game;
		window->clear(sf::Color::Black);
		window->display();
		if (t == 0){

			int k = this->drawSubMenu(lvl);
			
			if (k == 0){
				
				return this->newGame(lvl);
			}

			else if (k == 1)
			{
				return this->newGame(saveGame(lvl));
			}

			else if (k == 2){

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
				case 3:
					return music();
					break;
				case 4:
					return exit();
					break;
				}
			}
		}
		else if (t == -1){
			int k = drawLoseMenu();
			if (k == 0){
				return this->newGame();
			}
			else if (k == 1){
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
				case 3:
					return music();
					break;
				case 4:
					return exit();
					break;
				}
			}
		}

		
	}

	int saveGame(const int& Level) {
		window->clear();

		sf::Texture texture;
		sf::Font font;

		texture.loadFromFile("logo.png");
		font.loadFromFile("Animated.ttf");

		std::ofstream out;
		std::ifstream in;

		sf::Sprite sprite(texture);
		Button instruction("Enter your name", { 400, 50 }, 40, sf::Color::Green, sf::Color::Black);
		Button input_box("", { 720, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
		Button enter("Save", { 150, 50 }, 40, sf::Color::Green, sf::Color::Black);

		std::string name = "";
		sf::String sentence;
		sf::Text text(sentence, font, 40);

		text.setColor(sf::Color::Black);

		sprite.setPosition(sf::Vector2f(360, 250));
		instruction.set_position({ (float)350, (float)50 });
		input_box.set_position_input({ (float)110, (float)140 });
		enter.set_position({ (float)840, (float)140 });
		text.setPosition({ (float)140, (float)140 });

		instruction.set_font(font);
		enter.set_font(font);

		while (window->isOpen() && name.length() == 0)
		{
			sf::Event Event;
			while (window->pollEvent(Event)) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (enter.isMouse(*window))
					{
						name = sentence.toAnsiString();
						break;
					}
				}

				if (Event.type == sf::Event::TextEntered) {
					if (Event.text.unicode >= 32 && Event.text.unicode <= 126 && sentence.getSize() <= 36)
						sentence += (char)Event.text.unicode;
					else if (Event.text.unicode == 8 && sentence.getSize() > 0)
						sentence.erase(sentence.getSize() - 1);
					text.setString(sentence);
				}

			}

			window->draw(sprite);
			instruction.drawto(*window);
			input_box.drawto(*window);
			enter.drawto(*window);
			enter.isMouse(*window);
			window->draw(text);

			window->display();
			window->clear();
		}

		///// SAVING GOES HERE /////

		in.open("load_list.txt", std::ios::in);

		if (!in.is_open())
			std::cout << "Coundn't open load file\n";
		else
		{
			std::vector <std::pair<std::string, int>> list;
			int level;
			std::string info;
			std::string account;
			std::string lvl;
			bool flag = 0;

			while (!in.eof())
			{
				getline(in, info, '\n');

				for (int i = 0; i < info.length(); ++i)
				{
					if (info[i] != ',')
						account += info[i];
					else
					{
						lvl += info[i + 1];
						level = stoi(lvl);
						break;
					}
				}

				if (account == name)
				{
					flag = 1;
					level = Level;
				}
				
				std::pair<std::string, int> a(account, level);
				list.push_back(a);

				account.clear();
				lvl.clear();
				info.clear();
			}

			in.close();

			if (flag == 1)
				out.open("load_list.txt");
			else
				out.open("load_list.txt", std::ios::app);

			if (!out.is_open())
				std::cout << "Coundn't open load file\n";
			else
			{
				if (flag == 1)
				{
					for (auto it = list.begin(); it != list.end(); ++it)
						out << it->first << "," << it->second << '\n';
				}
				else
				{
					out << name << "," << Level << '\n';
				}
				out.close();
			}
			
			return Level;
		}
		return 1;
	}

	int loadLevel(const sf::String& name)
	{
		std::ifstream in;
		std::ofstream out;
		std::string account;
		std::string info;
		std::string lvl;
		int level = 1;

		in.open("load_list.txt", std::ios::in);

		if (!in.is_open())
			std::cout << "Coundn't open load file\n";
		else
		{
			while (!in.eof())
			{
				getline(in, info, '\n');

				for (int i = 0; i < info.length(); ++i)
				{
					if (info[i] != ',')
						account += info[i];
					else if (info[i] == ',' && account == name)
					{
						lvl += info[i + 1];
						level = stoi(lvl);
						in.close();
						return level;
					}
				}

				account.clear();
			}

			in.close();
		}

		out.open("load_list.txt", std::ios::app);
		if (!out.is_open())
			std::cout << "Coundn't open load file\n";
		else
		{
			out << "autosave," << 1 << '\n';
			out.close();
		}
		std::cout << "Load account is not existing! Created auto load account!\n";

		return level;
	}

	int loadGame(){
		window->clear();

		sf::Texture texture;
		sf::Font font;

		texture.loadFromFile("logo.png");
		font.loadFromFile("Animated.ttf");

		sf::Sprite sprite(texture);
		Button instruction("Enter your name", { 400, 50 }, 40, sf::Color::Green, sf::Color::Black);
		Button input_box("", { 720, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
		Button enter("Load", { 150, 50 }, 40, sf::Color::Green, sf::Color::Black);

		std::string name = "";
		sf::String sentence;
		sf::Text text(sentence, font, 40);

		text.setColor(sf::Color::Black);

		sprite.setPosition(sf::Vector2f(360, 250));
		instruction.set_position({(float)350, (float)50});
		input_box.set_position_input({ (float)110, (float)140 });
		enter.set_position({ (float)840, (float)140 });
		text.setPosition({ (float)140, (float)140 });

		instruction.set_font(font);
		enter.set_font(font);

		while (window->isOpen() && name.length() == 0)
		{
			sf::Event Event;
			while (window->pollEvent(Event)) {

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (enter.isMouse(*window))
					{
						name = sentence.toAnsiString();
						break;
					}
				}

				if (Event.type == sf::Event::TextEntered) {
					if (Event.text.unicode >= 32 && Event.text.unicode <= 126 && sentence.getSize() <= 36)
						sentence += (char)Event.text.unicode;
					else if (Event.text.unicode == 8 && sentence.getSize() > 0)
						sentence.erase(sentence.getSize() - 1);
					text.setString(sentence);
				}

			}

			window->draw(sprite);
			instruction.drawto(*window);
			input_box.drawto(*window);
			enter.drawto(*window);
			enter.isMouse(*window);
			window->draw(text);

			window->display();
			window->clear();
		}
		return newGame(loadLevel(name));
	}

	int rank(){
		window->clear();
		window->display();
		//prepare
		std::vector<std::string> info;
		std::vector<int> theLevel;
		std::vector<sf::Text> text;

		//readfile
		std::ifstream in;
		in.open("user.txt");

		//safe and read file
		if (!in.is_open()){
			this->window->close();
		}
		else{
			std::string tmp;
			int lv;
			while (!in.eof()){
				getline(in, tmp);
				in>>lv;
				in.ignore(10, '\n');
				theLevel.push_back(lv);
				info.push_back(tmp+" "+std::to_string(lv));
			}
		}
		in.close();

		//sort
		for (int i=0; i<theLevel.size()-1; ++i){
			for (int j=i+1; j<theLevel.size(); ++j){
				if (theLevel.at(j)>theLevel.at(i)){
					swap(theLevel.at(i), theLevel.at(j));
					swap(info.at(i), info.at(j));
				}
			}
		}

		//display
		for (int i=0; i<theLevel.size(); ++i){
			sf::Text tex;
			sf::Font font;
			font.loadFromFile("Animated.ttf");
			tex.setFont(font);
			tex.setPosition(sf::Vector2f(
				this->window->getSize().x/2,
				50.f*i
			));
			tex.setString(info.at(i));
			tex.setCharacterSize(40);

			text.push_back(tex);
		}

		int n;
		if (theLevel.size()>=5){
			n=5;
		}
		else{
			n=theLevel.size();	
		}
		
		for (int i=0; i<n; ++i){
			window->draw(text.at(i));
		}

		window->display();
		
		//press enter to exit
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
			return this->drawMenu();
		}

		return 0;
	}

	template<class T>
	void swap(T& a, T& b){
		T c;
		c=a;
		a=b;
		b=c;
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

	int drawSubMenu(const int& currentLevel){
		window->clear();
		std::string menu[3] = {"Resume", "Save game", "Exit"};
		sf::Text text[2];
		std::vector <Button> menu_button;
		sf::Font font;
		sf::Texture texture;
		std::string curLevel = "Current level: " + std::to_string(currentLevel);
		Button level(curLevel, { 600, 70 }, 60, sf::Color::Cyan, sf::Color::Black);


		texture.loadFromFile("logo.png");

		sf::Sprite sprite(texture);
		int i;

		font.loadFromFile("Animated.ttf");
		sprite.setPosition(sf::Vector2f(190, 100));
		level.set_position({ 250, 80 });
		level.set_font(font);


		for (i = 0; i < 3; ++i) {
			Button a(menu[i], { 200, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
			a.set_position(sf::Vector2f(window->getSize().x / 2 + 110, i * 65 + 250));
			a.set_font(font);
			menu_button.push_back(a);
		}

		while (window->isOpen()){
			this->pollEvents();
			for (i = 0; i < 3; ++i){
				menu_button[i].drawto(*window);
			}
			level.drawto(*window);
			window->draw(sprite);
			window->display();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				for (i = 0; i < 3; ++i) {
					if (menu_button[i].isMouse(*window))
						return i;
				}
			}

			for (i = 0; i < 3; ++i) {
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
			Button a(menu[i], { 190, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
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

	//////////////////// SOUND MANIPULATE ////////////////////
	std::string set_sound()
	{
		bg_music = !bg_music;
		play_sound();
		if (bg_music)
			return "Music: ON";
		return "Music: OFF";
	}

	void play_sound()
	{
		if (bg_music)
			sound_track.play();
		else
			sound_track.pause();
	}
};




#endif 