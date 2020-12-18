#include "CGame.h"

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
			break;
		}
	}
}

void CGame::initVariables(){
   this->score=0;
   this->elapsed=0.01f;
   this->cheatMode=false; 
   player.setPosition(sf::Vector2f(375, 625));

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

	//update player, traffic
    this->player.update(event, *window);
    trafficManager.update(elapsed, gameTime);
}

bool CGame::isRunning(){
    return this->window->isOpen();
}

void CGame::render()
{
	this->window->clear();
    this->initBackground();
	//Render stuff
	// this->player.render(this->window);

	// for (auto i : this->swagBalls)
	// {
	// 	i.render(*this->window);
	// }

	// //Render gui
	// this->renderGui(this->window);

	// //Render end text
	// if(this->endGame == true)
	// 	this->window->draw(this->endGameText);
    // clear the window with black color for start of drawing a new frame
    window->clear(sf::Color::Black);

    // Draw game componenets to the screen
    background.draw(*window);
    player.draw(*window);
    trafficManager.draw(*window);

    // Draw UI elements to the screen
    // textLives.draw(*window);
    // textTime.draw(*window);
    // textMoves.draw(*window);
	this->window->display();
}