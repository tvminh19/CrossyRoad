// Author: Mitch Barnett
// Created: April 2016

#ifndef MOVABLE_H
#define MOVABLE_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

// A basic class for movable rectangular objects
class Movable : public Entity
{
public:
	// Returns the x,y coordinates of the object
	sf::Vector2f getPosition();

	// Returns true if the object is currently on the screen
	bool onScreen(sf::RenderWindow&);

	// Returns true if the object would be on the screen after a passed transformation
	bool onScreen(sf::RenderWindow&, sf::Vector2f transformation);

	// Returns true if it collides the the passed rectangle
	bool checkCollision(sf::FloatRect other);
	// sets the positon of the object
	void setPosition(sf::Vector2f transformation);
};

#endif
