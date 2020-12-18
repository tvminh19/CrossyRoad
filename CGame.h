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
	bool cheatMode;

    //TextItem textLives("Lives: ", player.getLivesLeft(), sf::Vector2f(0,650));	// Creates Lives UI item
	// TextItem textMoves("Moves: ", player.getMovesTaken(), sf::Vector2f(675, 650));	// Creates Moves UI item
	// TextItem textTime("Time: ", 0.0f, sf::Vector2f(300, 650));				// Creates Time UI item			
	// TextItem textCheatMode("Cheatmode on", sf::Vector2f(0, 0), 50); // show text saying cheatmode is on

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
