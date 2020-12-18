#ifndef CMenu_H
#define CMenu_H
#pragma warning(disable : 4996)


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#define MENU_CHOICE 5


class CMenu {
private:
	int selected;
	bool music;
	sf::Font font;
	sf::Text menu[MENU_CHOICE];
public:
	CMenu(const float& width, const float& height);
	~CMenu();
	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int get_choice();
};

#endif // !CMenu_H
