// Author: Mitch Barnett
// Created: April 2016

#include "CPlayer.h"
//test xyz

// Creates a CPlayer object that can be controlled by a user
CPlayer::CPlayer()
{
	// Set initial values
	m_iMoves = 0;
	m_iLivesLeft = 3;
	m_rectBox.setSize(sf::Vector2f(50, 50));

	// Load the CPlayer texture
	texPlayerTexture.loadFromFile("assets/textures/frog.png");
	m_rectBox.setTexture(&texPlayerTexture);

	// Set the origin to the center of the CPlayer for rotation purposes
	m_rectBox.setOrigin(m_rectBox.getSize().x / 2, m_rectBox.getSize().y / 2);
}

int CPlayer::getLivesLeft() {return m_iLivesLeft;}

int CPlayer::getMovesTaken() {return m_iMoves;}

void CPlayer::loseLife() {m_iLivesLeft--;}


void CPlayer::moveLeft()
{
	setPosition(getPosition()+ sf::Vector2f(-50,0));
	m_rectBox.setRotation(270);
}
void CPlayer::moveRight()
{
	setPosition(getPosition() + sf::Vector2f(50, 0));
	m_rectBox.setRotation(90);
}
void CPlayer::moveUp()
{
	setPosition(getPosition() + sf::Vector2f(0, -50));
	m_rectBox.setRotation(0);
}
void CPlayer::moveDown()
{
	setPosition(getPosition() + sf::Vector2f(0, 50));
	m_rectBox.setRotation(180);
}

// Check if there is a key input corisponding to a movement (arrow keys)
// Check that the is not an active cooldown
// Check that after performing the move the CPlayer will be compltyly on the screen
// if all are true perform the move, increment the move counter variable, start the cooldown
void CPlayer::checkMovement(sf::Event& event, sf::RenderWindow& window)
{
	sf::Time cooldown = sf::seconds(0.25f); // cooldown of 0.25 seconds
	if (event.type == sf::Event::KeyPressed &&  moveCooldownClock.getElapsedTime() > cooldown) // check for keypress and cooldown

	{
		if (event.key.code == sf::Keyboard::Left && onScreen(window, sf::Vector2f(-50, 0)))
		{
			moveLeft();
			moveCooldownClock.restart();
			m_iMoves++;
		}
		else if (event.key.code == sf::Keyboard::Right && onScreen(window, sf::Vector2f(50, 0)))
		{
			moveRight();
			moveCooldownClock.restart();
			m_iMoves++;
		}
		else if (event.key.code == sf::Keyboard::Up && onScreen(window, sf::Vector2f(0, -50)))
		{
			moveUp();
			moveCooldownClock.restart();
			m_iMoves++;
		}
		else if (event.key.code == sf::Keyboard::Down && onScreen(window, sf::Vector2f(0, 50)))
		{
			moveDown();
			moveCooldownClock.restart();
			m_iMoves++;
		}
	}
}

// Updates the players position
void CPlayer::update(sf::Event& event, sf::RenderWindow& window)
{
	checkMovement(event, window);
}

//reset to inital values for game restart
void CPlayer::reset()
{
	m_iLivesLeft = 3;
	m_iMoves = 0;
	setPosition(sf::Vector2f(375, 625));
	m_rectBox.setRotation(0);
}
