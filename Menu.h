#ifndef _MENU_H_
#define _MENU_H_

#pragma warning(disable : 4996)

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <fstream>


class Button {
private:
	sf::RectangleShape button;
	sf::Text text;
	sf::Color bgColor;
public:
	Button();

	Button(const std::string& t, const sf::Vector2f& size, const int& charSize, const sf::Color& background, const sf::Color& textColor);

	void set_font(const sf::Font& font);

	void set_position(const sf::Vector2f& pos);

	void set_position_2(const sf::Vector2f& pos);

	void set_position_input(const sf::Vector2f& pos);

	void set_string(const std::string& t);


	void drawto(sf::RenderWindow& window);


	bool isMouse(sf::RenderWindow& window);

	~Button();
};


class Menu{
private:
	sf::RenderWindow* window=nullptr;
	sf::Event* event=nullptr;
	sf::VideoMode videoMode;
	Game* game=nullptr;
	bool bg_music;
	sf::Music sound_track;

	void initWindow();

public:
	//cons & des
	Menu();
	
	~Menu();
	/**
	 * draw the menu
	 * return the choices
	 * 0 -> newGame
	 * 1 -> loadGame
	 * 2 -> Ranking
	 * 3 -> Music
	 * 4 -> Exit
	 */
	int drawMenu();

	int newGame(const int& level = 1);

	int saveGame(const int& Level);

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
			while (in >> info)
			{

				for (int i = 0; i < info.length(); ++i)
				{
					if (info[i] != ',')
						account += info[i];
					else if (info[i] == ',' && account == name)
					{
						while (i + 1 < info.length())
							lvl += info[++i];

						level = stoi(lvl);
						in.close();
						std::cout << "Loaded account" << " \"" << account << "\" " << "successfully!\n";
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

		std::cout << "Load account is not existing! Loading autosave account!\n";

		return level;
	}

	int loadGame();

	int rank();

	template<class T> void swap(T& a, T& b);

	int exit_game();

	sf::RenderWindow* getWindow();

	void pollEvents();

	int drawSubMenu(const int& currentLevel);

	int drawLoseMenu();

	//////////////////// SOUND MANIPULATE ////////////////////
	std::string set_sound();

	void play_sound();
};




#endif 


