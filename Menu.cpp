#include "Menu.h"


//////////////////////// MENU FUNCTION //////////////////////////

Menu::~Menu() {
	delete window;
}

Menu::Menu(){
	this->initWindow();
	int width=this->window->getSize().x;
	int heigh=this->window->getSize().y;

	if (!font.loadFromFile("arial.ttf")) exit(0);
	else std::cout << "GAME STARTED!\n";

	std::string choices[MENU_CHOICE] = { "New game", "Load game", "Ranking", "Sound: ON", "Exit" };

	for (int i = 0; i < 5; ++i)
	{
		menu[i].setFont(font);
		menu[i].setCharacterSize(45);
		if (i == 0)
			menu[i].setColor(sf::Color::Red);
		else
			menu[i].setColor(sf::Color::Cyan);
		menu[i].setString(choices[i]);
		menu[i].setPosition(sf::Vector2f(width / 2 - 75, i * 62 + 350));
	}

	sound = true;
	if (!sound_track.openFromFile("music.ogg"))
	{
		std::cout << "Couldn't load music file!\nGuess there will be no music :(\n";
	}
	sound_track.setPlayingOffset(sf::seconds(7.f));
	sound_track.setVolume(40);
	sound_track.setLoop(true);
	selected = 0;
}

void Menu::draw(sf::RenderWindow& window)
{
	window.clear();

	sf::Texture texture;
	if (!texture.loadFromFile("logo.png"))	exit(0);
	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(360, 10));
	window.draw(sprite);

	for (int i = 0; i < MENU_CHOICE; ++i)
		window.draw(menu[i]);

}

void Menu::MoveUp()
{
	if (selected > 0)
	{
		menu[selected].setColor(sf::Color::Cyan);
		selected--;
		menu[selected].setColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selected < MENU_CHOICE - 1)
	{
		menu[selected].setColor(sf::Color::Cyan);
		selected++;
		menu[selected].setColor(sf::Color::Red);
	}
}

void Menu::set_sound()
{
	sound = !this->get_sound();
	play_sound();
	if (sound)
		menu[3].setString("Sound: ON");
	else
		menu[3].setString("Sound: OFF");
}

void Menu::set_level(const int& lvl)
{
	level = lvl;
}

void Menu::play_sound()
{
	if (sound)
		sound_track.play();
	else
		sound_track.pause();
}

int Menu::get_choice()
{
	return selected;
}

bool Menu::get_sound()
{
	return sound;
}

//////////////////////// GAME FUNCTION //////////////////////////

void Menu::LoadGame(sf::RenderWindow& window)
{
	sf::Texture texture;
	if (!texture.loadFromFile("logo.png"))	exit(0);
	sf::Sprite sprite(texture);
	sprite.setPosition(sf::Vector2f(360, 10));
	window.draw(sprite);

	std::string name = "";
	sf::String sentence;
	sf::Text text(sentence, font, 30);

	text.setColor(sf::Color::Cyan);
	text.setPosition(sf::Vector2f(window.getSize().x / 2 - 100, 450));
	
	
	while (name.length() == 0)
	{ 
		sf::Event Event;
  		while (window.pollEvent(Event))
		{
			if (name.length() == 0) {
				switch (Event.type)
				{
				case sf::Event::Closed:
					std::cout << "GAME STOPPED!\n";
					window.close();
					exit(0);
				case sf::Event::KeyPressed:
					if (Event.key.code == sf::Keyboard::Enter)
						name = sentence.toAnsiString();
					break;
				case sf::Event::TextEntered:
					if (Event.text.unicode >= 32 && Event.text.unicode <= 126)
						sentence += (char)Event.text.unicode;
					else if (Event.text.unicode == 8 && sentence.getSize() > 0)
						sentence.erase(sentence.getSize() - 1, sentence.getSize());
					text.setString(sentence);
					break;
				default:
					break;
				}
			}
			else break;
			window.draw(text);
			window.display();
		}
	}
}

