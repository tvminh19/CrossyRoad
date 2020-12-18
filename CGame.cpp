#include "CGame.h"

int calcScore(float fTime, int iMoves, int iLives)
{
	int iTimeScore = (int)(fTime);		// Converts the float time to and int score
	return (iTimeScore + iMoves - iLives * 5) + 1;	// Takes all values to return a score
}


void CGame::pollEvents(){
	//Event polling
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			else if (this->event.key.code == sf::Keyboard::R){
				player.reset();
				gameClock.restart();
			}
			break;
		}
	}
}

void CGame::initVariables(){
	this->score=0;
	this->elapsed=0.01f;
	player.setPosition(sf::Vector2f(375, 625));
	
	textLives.setTextItem("Lives: ", player.getLivesLeft(), sf::Vector2f(0,650));	// Creates Lives UI item
	textMoves.setTextItem("Moves: ", player.getMovesTaken(), sf::Vector2f(675, 650));	// Creates Moves UI item
	textTime.setTextItem("Time: ", 0.0f, sf::Vector2f(300, 650));				// Creates Time UI item			
	textCheatMode.setTextItem("Cheatmode on", sf::Vector2f(0, 0), 50); // show text saying cheatmode is on
}

void CGame::initWindow(){
    this->videoMode.height = 680;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this->videoMode, "Crossy Road", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void CGame::initBackground(){
    //draw background
    this->background.draw(*window);
    
    //draw player

    //draw trafficManager
    trafficManager.draw(*window);
}

CGame::CGame(){
    this->initVariables();
    this->initWindow();
    this->initBackground();
}

void CGame::update()
{
	this->pollEvents();
	frameClock.restart();
	//update player, traffic
    this->player.update(event, *window);
    trafficManager.update(elapsed, gameTime);

	// Checks for a collision between the player and traffic objects
	if (trafficManager.checkCollision(player.getBounds())){
		player.loseLife();	// Decrement the lives
		player.setPosition(sf::Vector2f(375, 625));
	}

	// Updates UI elements
	textLives.update("Lives: ", player.getLivesLeft());
	textTime.update("Time: ", gameClock.getElapsedTime().asSeconds());
	textMoves.update("Moves: ", player.getMovesTaken());
}

bool CGame::isRunning(){
    return this->window->isOpen();
}

void CGame::render()
{
	this->window->clear(sf::Color::Black);
    this->initBackground();

    // Draw game componenets to the screen
    background.draw(*window);
    player.draw(*window);
    trafficManager.draw(*window);

    // Draw UI elements to the screen
    textLives.draw(*window);
    textTime.draw(*window);
    textMoves.draw(*window);

	// Draw a the game over screen if game is lost
	if (player.getLivesLeft() <= 0)
	{
		window->clear(sf::Color::Black);
		TextItem gameOver;
		gameOver.setTextItem("Game Over", sf::Vector2f(250, 200), 60);
		TextItem rToRestart;
		rToRestart.setTextItem("Press r to restart", sf::Vector2f(300, 400), 30);
		gameOver.draw(*window);
		rToRestart.draw(*window);
	}

	// Draw the game win screen is game is won
	else if (player.getBounds().intersects(background.m_rectTopPavement.getGlobalBounds())){
		// Calculate the score
		// Create UI items for the game over screen
		TextItem textGameWin;
		textGameWin.setTextItem("Congratulations", sf::Vector2f(200, 250), 60);
		TextItem textGameScore;
		textGameScore.setTextItem("Score:  ", score, sf::Vector2f(350, 320));
		TextItem textRestart;
		textRestart.setTextItem("Press r to play again", sf::Vector2f(275, 400), 30);

		// Draw the game over message to the screen
		window->clear(sf::Color::Black);
		textGameWin.draw(*window);
		textGameScore.draw(*window);
		textRestart.draw(*window);
		}
		else
		{
			// Calculate the score
			score = calcScore(gameTime, player.getMovesTaken(), player.getLivesLeft());
		}

	this->window->display();
}