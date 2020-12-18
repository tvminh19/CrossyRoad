// Author: Mitch Barnett
// Created: April 2016

#include "Movable.h"

// Returns the position of the object
sf::Vector2f Movable::getPosition()
{
	return m_rectBox.getPosition();
}

// Checks if the object is totaly on the screen
bool  Movable::onScreen(sf::RenderWindow& window)
{
	sf::Vector2f vec2LocalPoint;	// The relative position of the current point
	sf::Vector2f vec2PointPosition; // The actual position of the point

	// Loops through each point the the object
	for (unsigned int i = 0; i < m_rectBox.getPointCount(); i++)
	{
		// set relative position of the current point
		vec2LocalPoint = (m_rectBox.getPoint(i) - m_rectBox.getOrigin());	
		// Adds the objects global position to the points relitive position to get the points actual position
		vec2PointPosition = (getPosition() + vec2LocalPoint);

		// Checking if the point crosses any of the screen boundries
		if (vec2PointPosition.x > window.getSize().x)		{ return false; }	// too far left
		else if (vec2PointPosition.y > window.getSize().y)	{ return false; }	// too far down
		else if (vec2PointPosition.x < 0)	{ return false; } // too far right
		else if (vec2PointPosition.y < 0)	{ return false; } // too far up
	}
	return true; // return true as no points have gone out of the screen
}

// Checks if the object is totaly on the screen after applying a translation
bool  Movable::onScreen(sf::RenderWindow& window, sf::Vector2f transformation)
{
	
	sf::Vector2f vec2GlobalPos(getPosition() + transformation); // Store the objets position after the transformation
	sf::Vector2f vec2LocalPoint;	// the relative position of the current point 
	sf::Vector2f vec2PointPosition; // The actual position of the point

	// // Loops through each point the the object
	for (unsigned int i = 0; i < m_rectBox.getPointCount(); i++)
	{
		// set relative position of the current point
		vec2LocalPoint = (m_rectBox.getPoint(i) - m_rectBox.getOrigin());
		// Adds the objects global position to the points relitive position to get the points actual position
		vec2PointPosition = (vec2GlobalPos + vec2LocalPoint);

		if (vec2PointPosition.x > window.getSize().x)		{ return false; } // too far left
		else if (vec2PointPosition.y > window.getSize().y)	{ return false; } // too far down
		else if (vec2PointPosition.x < 0)	{ return false; } // too far right
		else if (vec2PointPosition.y < 0)	{ return false; } // too far up
	}
	return true; // return true as no points have gone out of the screen
}

// Returns true if there this objects retangle bounding box intercets witht the passed one
bool  Movable::checkCollision(sf::FloatRect other)
{
	if (getBounds().intersects(other)) {return true;}
	else {return false;}
}

// Sets the position of the object
void  Movable::setPosition(sf::Vector2f transformation)
{
	m_rectBox.setPosition(transformation);
}
