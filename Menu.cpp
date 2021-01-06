#include "Menu.h"

Button::Button() {}

Button::Button(const std::string& t, const sf::Vector2f& size, const int& charSize, const sf::Color& background, const sf::Color& textColor)
{
	text.setString(t);
	text.setColor(textColor);
	text.setCharacterSize(charSize);
	button.setSize(size);
	button.setFillColor(background);
	bgColor = background;
}

void Button::set_font(const sf::Font& font)
{
	text.setFont(font);
}

void Button::set_position(const sf::Vector2f& pos)
{
	button.setPosition(pos);
	float x = (pos.x + button.getLocalBounds().width / 3) - (text.getLocalBounds().width / 2) - 40;
	float y = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 2) - 15;
	text.setPosition(sf::Vector2f(x, y));
}

void Button::set_position_2(const sf::Vector2f& pos)
{
	button.setPosition(pos);
	float x = (pos.x + button.getLocalBounds().width / 3) - (text.getLocalBounds().width / 2) - 40;
	float y = (pos.y + button.getLocalBounds().height / 3) - (text.getLocalBounds().height / 2) - 15;
	text.setPosition(sf::Vector2f(pos.x + 15, pos.y - 0.5));
}

void Button::set_position_input(const sf::Vector2f& pos)
{
	button.setPosition(pos);
	float x = (pos.x + button.getLocalBounds().width / 5) - (text.getLocalBounds().width / 2) - 40;
	float y = (pos.y + button.getLocalBounds().height / 5) - (text.getLocalBounds().height / 2) - 15;
	text.setPosition(sf::Vector2f(x, y));
}

void Button::set_string(const std::string& t)
{
	text.setString(t);
}

void Button::drawto(sf::RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouse(sf::RenderWindow& window)
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

Button::~Button() {}

void Menu::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1080;
	window = new sf::RenderWindow(
		this->videoMode,
		"Crossy Road",
		sf::Style::Default
	);
	this->window->setFramerateLimit(60);
}

Menu::Menu()
{
	//initWindow
	this->game = new Game;
	this->event = new sf::Event;
	this->initWindow();
	//Background music
	this->bg_music = true;
	this->sound_track.openFromFile("music.ogg");
	this->sound_track.setPlayingOffset(sf::seconds(15.f));
	this->sound_track.setVolume(12);
	this->sound_track.setLoop(true);
	play_sound();
}

Menu::~Menu()
{
	delete window;
	delete game;
	delete event;
}

int Menu::drawMenu()
{
	window->clear();

	std::string menu[5] = { "New Game", "Load Game", "Ranking", "Music: ON", "Exit" };
	std::vector <Button> menu_button;
	sf::Font font;
	sf::Texture texture;

	if (!bg_music) menu[3] = "Music: OFF";

	texture.loadFromFile("logo.png");

	sf::Sprite sprite(texture);
	int i;

	font.loadFromFile("Animated.ttf");
	sprite.setPosition(sf::Vector2f(360, 10));


	for (i = 0; i < 5; ++i) {
		Button a(menu[i], { 190, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
		a.set_position_2({ (float)450 , (float)i * 60 + 350 });
		a.set_font(font);
		menu_button.push_back(a);
	}

	sf::Clock clock;
	sf::Time time = sf::seconds(0.10f);
	clock.restart().asSeconds();

	while (window->isOpen()) {
		this->pollEvents();
		for (i = 0; i < 5; ++i) {
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

int Menu::newGame(const int& level)
{
	std::cout << "GAME STARTED!!!\n";

	this->game->setLevel(level);

	int t = this->game->runGame(*window);
	int lvl = this->game->getLevel();

	delete game;
	game = new Game;

	window->clear(sf::Color::Black);
	window->display();

	if (t == 0) {

		int k = this->drawSubMenu(lvl);

		if (k == 0) {
			return this->newGame(lvl);
		}

		else if (k == 1) {
			return this->newGame(saveGame(lvl));
		}

		else if (k == 2) {
			return this->newGame(loadGame());
		}

		else if (k == 4) {

			switch (this->drawMenu()) {
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
				return exit_game();
				break;
			}
		}
	}
	else if (t == -1) {
		int k = drawLoseMenu();
		if (k == 0) {
			return this->newGame();
		}
		else if (k == 1) {
			switch (this->drawMenu()) {
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
				return exit_game();
				break;
			}
		}
	}


}

int Menu::saveGame(const int& Level)
{
	window->clear();

	sf::Texture texture;
	sf::Font font;

	texture.loadFromFile("logo.png");
	font.loadFromFile("Animated.ttf");

	std::ofstream out;
	std::ifstream in;

	sf::Sprite sprite(texture);
	Button instruction("Enter your name", { 400, 50 }, 40, sf::Color::Green, sf::Color::Black);
	Button input_box("", { 690, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
	Button enter("Save", { 150, 50 }, 40, sf::Color::Green, sf::Color::Black);

	std::string name = "";
	sf::String sentence;
	sf::Text text(sentence, font, 40);

	text.setColor(sf::Color::Black);

	sprite.setPosition(sf::Vector2f(360, 250));
	instruction.set_position({ (float)350, (float)50 });
	input_box.set_position_input({ (float)125, (float)140 });
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

		while (in >> info)
		{

			for (int i = 0; i < info.length(); ++i)
			{
				if (info[i] != ',')
					account += info[i];
				else
				{
					while (i + 1 < info.length())
						lvl += info[++i];

					level = stoi(lvl);
					break;
				}
			}

			if (account == name)
			{
				flag = 1;
				level = Level;
			}

			//std::pair<std::string, int> a(account, level);
			list.push_back(make_pair(account, level));

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
		std::cout << "Saved account" << " \"" << name << "\" " << "successfully!\n";

		return Level;
	}
	return 1;
}

int Menu::loadGame()
{
	window->clear();

	sf::Texture texture;
	sf::Font font;

	texture.loadFromFile("logo.png");
	font.loadFromFile("Animated.ttf");

	sf::Sprite sprite(texture);
	Button instruction("Enter your name", { 400, 50 }, 40, sf::Color::Green, sf::Color::Black);
	Button input_box("", { 690, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
	Button enter("Load", { 150, 50 }, 40, sf::Color::Green, sf::Color::Black);

	std::string name = "";
	sf::String sentence;
	sf::Text text(sentence, font, 40);

	text.setColor(sf::Color::Black);

	sprite.setPosition(sf::Vector2f(360, 250));
	instruction.set_position({ (float)350, (float)50 });
	input_box.set_position_input({ (float)125, (float)140 });
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
				if (Event.text.unicode >= 32 && Event.text.unicode <= 126 && sentence.getSize() <= 18)
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

int Menu::rank()
{
	while (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == false && window->isOpen()) {
		window->clear();
		//prepare
		std::vector<std::string> info;
		std::vector<int> theLevel;
		std::vector<std::pair<Button, Button>> box;
		std::vector<Button> num;
		Button title("TOP 5 BEST PLAYERS", { 688, 90 }, 80, sf::Color::Green, sf::Color::Black);
		sf::Text esc;
		sf::Font font;
		int i;

		esc.setString("Press Enter to return to Menu");
		font.loadFromFile("Animated.ttf");
		title.set_font(font);
		esc.setFont(font);
		esc.setColor(sf::Color::Cyan);
		esc.setCharacterSize(40);
		esc.setPosition(sf::Vector2f(310, 600));
		title.set_position_2(sf::Vector2f(200, 50));
		title.drawto(*window);
		window->draw(esc);

		//readfile
		std::ifstream fin;
		fin.open("load_list.txt", std::ios::in);

		//safe and read file
		if (!fin.is_open()) {
			this->window->close();

		}
		else {
			std::string info_line;
			std::string acc;
			std::string levell;
			int lv;
			while (fin >> info_line)
			{
				for (i = 0; i < info_line.length(); ++i)
				{
					if (info_line[i] != ',')
						acc += info_line[i];
					else
					{
						while (i + 1 < info_line.length())
							levell += info_line[++i];

						lv = stoi(levell);
						break;
					}
				}
				theLevel.push_back(lv);
				info.push_back(acc);

				acc.clear();
				levell.clear();
				info_line.clear();
			}
			fin.close();
		}

		//sort
		if (theLevel.size()) {
			for (i = 0; i < theLevel.size() - 1; ++i) {
				for (int j = i + 1; j < theLevel.size(); ++j) {
					if (theLevel.at(j) > theLevel.at(i)) {
						swap(theLevel.at(i), theLevel.at(j));
						swap(info.at(i), info.at(j));
					}
				}
			}
		}

		//display

		for (i = 0; i < theLevel.size(); ++i) {
			if (i < 5) {
				Button context(info[i], { 450, 70 }, 60, sf::Color::Yellow, sf::Color::Black);
				Button lvl(std::to_string(theLevel[i]), { 128, 70 }, 60, sf::Color::Yellow, sf::Color::Black);
				Button n(std::to_string(i + 1), { 60, 70 }, 60, sf::Color::Yellow, sf::Color::Black);

				context.set_font(font);
				lvl.set_font(font);
				n.set_font(font);
				context.set_position_2(sf::Vector2f(285, 75 * (i + 1) + 110));
				lvl.set_position_2(sf::Vector2f(760, 75 * (i + 1) + 110));
				n.set_position_2(sf::Vector2f(200, 75 * (i + 1) + 110));

				box.push_back(std::make_pair(context, lvl));
				num.push_back(n);

			}
			else break;
		}

		for (i = 0; i < box.size(); ++i) {
			box[i].first.drawto(*window);
			box[i].second.drawto(*window);
			num[i].drawto(*window);
		}
		window->display();
	}

	switch (this->drawMenu()) {
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
		return exit_game();
		break;
	}
}

int Menu::exit_game()
{
	std::cout << "GAME EXIT!!!\n";
	window->close();
	this->~Menu();
	exit(0);
	return 0;
}

sf::RenderWindow* Menu::getWindow()
{
	return this->window;
}

void Menu::pollEvents()
{
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

int Menu::drawSubMenu(const int& currentLevel)
{
	window->clear();
	std::string menu[5] = { "Resume", "Save game", "Load game", "Music: ON", "Exit" };
	sf::Text text[2];
	std::vector <Button> menu_button;
	sf::Font font;
	sf::Texture texture;
	std::string curLevel = "Current level: " + std::to_string(currentLevel);
	Button level(curLevel, { 600, 70 }, 60, sf::Color::Cyan, sf::Color::Black);
	if (!bg_music) menu[3] = "Music: OFF";

	texture.loadFromFile("logo.png");

	sf::Sprite sprite(texture);
	int i;

	font.loadFromFile("Animated.ttf");
	sprite.setPosition(sf::Vector2f(242, 100));
	level.set_position({ 250, 80 });
	level.set_font(font);

	sf::Clock clock;
	sf::Time time = sf::seconds(0.10f);
	clock.restart().asSeconds();

	for (i = 0; i < 5; ++i) {
		Button a(menu[i], { 200, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
		a.set_position(sf::Vector2f(window->getSize().x / 2 + 110, i * 65 + 220));
		a.set_font(font);
		menu_button.push_back(a);
	}

	while (window->isOpen()) {
		this->pollEvents();
		for (i = 0; i < 5; ++i) {
			menu_button[i].drawto(*window);
		}

		level.drawto(*window);
		window->draw(sprite);
		window->display();

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
		}

		for (i = 0; i < 5; ++i) {
			menu_button[i].isMouse(*window);
		}

		window->clear();
	}
	return 1;
}

int Menu::drawLoseMenu()
{
	window->clear();
	std::cout << "CRASHED :((\n";

	std::string menu[2] = { "Try again", "Quit" };
	sf::Text text[2];
	sf::Text crash_text;
	std::vector <Button> menu_button;
	sf::Font font;

	int i;

	font.loadFromFile("Animated.ttf");

	crash_text.setPosition(sf::Vector2f(140, 190));
	crash_text.setFont(font);
	crash_text.setString("CRASHED");
	crash_text.setCharacterSize(165);
	crash_text.setColor(sf::Color::Red);

	for (i = 0; i < 2; ++i) {
		Button a(menu[i], { 190, 50 }, 40, sf::Color::Cyan, sf::Color::Black);
		a.set_position(sf::Vector2f(window->getSize().x / 2 + 160, i * 65 + 250));
		a.set_font(font);
		menu_button.push_back(a);
	}

	while (window->isOpen()) {
		this->pollEvents();
		for (i = 0; i < 2; ++i) {
			menu_button[i].drawto(*window);
		}

		window->draw(crash_text);
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

std::string Menu::set_sound()
{
	sf::sleep(sf::seconds(0.175));
	bg_music = !bg_music;
	play_sound();
	if (bg_music) {
		std::cout << "Turning sound on!\n";
		return "Music: ON";
	}
	std::cout << "Turning sound off!\n";
	return "Music: OFF";
}

void Menu::play_sound()
{
	if (bg_music)
		sound_track.play();
	else
		sound_track.pause();
}

template<class T>
inline void Menu::swap(T& a, T& b)
{
	T c;
	c = a;
	a = b;
	b = c;
}

