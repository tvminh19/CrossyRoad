#include "CMenu.h"

CMenu::~CMenu() {}

CMenu::CMenu(const float& width, const float& height)
{
	if (!font.loadFromFile("E:/Crossing Road/tvminh19/CrossyRoad/src/Animated.ttf")) exit(0);
	else std::cout << "Game has been run\n";

	std::string choices[MENU_CHOICE] = { "New game", "Load game", "Ranking", "Setting", "Exit" };

	for (int i = 0; i < 5; ++i)
	{
		menu[i].setFont(font);
		if (i == 0)
			menu[i].setColor(sf::Color::Red);
		else
			menu[i].setColor(sf::Color::Cyan);
		menu[i].setString(choices[i]);
		menu[i].setPosition(sf::Vector2f(100, i * 50 + 100));
	}

	music = true;
	selected = 0;
}

void CMenu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MENU_CHOICE; ++i)
	{
		window.draw(menu[i]);
	}


	sf::Texture texture;
	if (!texture.loadFromFile("E:/Crossing Road/tvminh19/CrossyRoad/src/logo.png"))	exit(0);
	sf::Sprite sprite(texture);

	sprite.setPosition(sf::Vector2f(300, 10));
	window.draw(sprite);
}

void CMenu::MoveUp()
{
	if (selected > 0)
	{
		menu[selected].setColor(sf::Color::Cyan);
		selected--;
		menu[selected].setColor(sf::Color::Red);
	}
}

void CMenu::MoveDown()
{
	if (selected < MENU_CHOICE - 1)
	{
		menu[selected].setColor(sf::Color::Cyan);
		selected++;
		menu[selected].setColor(sf::Color::Red);
	}
}

int CMenu::get_choice()
{
	return selected;
}


