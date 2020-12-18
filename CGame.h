#ifndef _CGAME_H_
#define _CGAME_H_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Background.h"
#include "TrafficManager.h"
#include "TextItem.h"
#include "CPlayer.h"



class CGame{
private:
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event event;
    float gameTime = gameClock.getElapsedTime().asSeconds();
    CPlayer player;
    TrafficManager trafficManager;
    Background background;
    int score;
    float elapsed;	// Stores the value of the frame time

    TextItem textLives;
	TextItem textMoves;
	TextItem textTime;
	TextItem textCheatMode;

	sf::Clock gameClock;	// A clock to track how long the game has been running
	sf::Clock frameClock;	// Tracks how much time the last frame took

    void initVariables();
    void initText();
    void initBackground();
    void initPlayer();
    void initWindow();
    void pollEvents();
public:
    CGame();
    // ~CGame();

    bool isRunning();

    void update();
    void render();
};











#endif
