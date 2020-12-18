// Author: Mitch Barnett
// Created: April 2016

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Movable.h"

// Creates a CPlayer object that can be controlled by a user
class CPlayer : public Movable
{
public:
	// Constructor
	CPlayer();

	//resets to default values;
	void reset();

	// Returns the lives the CPlayer has remaining
	int getLivesLeft();	

	// Returns the number of moves the CPlayer has took
	int getMovesTaken();

	// Decrements the number of lives the CPlayer has left
	void loseLife();

	// Checks for user input and makes the appropiate move if possible
	void checkMovement(sf::Event& event, sf::RenderWindow& window);	

	// Updates the players position
	void update(sf::Event& event, sf::RenderWindow& window);
	
private:
	int m_iLivesLeft;	// The number of lives the CPlayer has left
	int m_iMoves;		// The number of moves the CPlayer has made
	sf::Clock moveCooldownClock; // Keeps track of the cooldown of when the CPlayer cannot move
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	sf::Texture texPlayerTexture; // Holds the texture for the CPlayer
};

#endif
