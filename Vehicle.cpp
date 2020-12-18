// Author: Mitch Barnett
// Created: April 2016

#include "Vehicle.h"

// Constructor
Vehicle::Vehicle(float fSpeed, float fXPos, float fYPos, float fLength, std::vector<sf::Texture*> vptexTextures)
{
	m_fX = fXPos;
	m_fY = fYPos;
	m_fSpeed = fSpeed;
	m_fLength = fLength;
	m_fWidth = 46;
	m_rectBox.setPosition(sf::Vector2f(m_fX, m_fY));		// Sets the position of the vehicle
	m_rectBox.setSize(sf::Vector2f(m_fLength, m_fWidth));	// Sets the size of the vehicle

	int iRandomIndex = rand() % vptexTextures.size();		// Picks a random texture
	m_rectBox.setTexture(vptexTextures[iRandomIndex]);		// Applys the random texture to the vehicle

	if (m_fSpeed < 0)
	{
		m_rectBox.scale(-1, 1);		// Reverses the texture if the vehicle is traveling left
	}
}

// Sets a new speed for the vehicle
void Vehicle::setSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}

// Updates the vehicles position
void Vehicle::update(float elapsed)
{
	m_fX += m_fSpeed * elapsed;	// adds the speed(pixels per second) x elapsed(seconds)  to the current x
	m_rectBox.setPosition(sf::Vector2f(m_fX, m_fY + 2.0f));	// Sets the vehicles position using the new value
}

// Draws vehicle to the provided window
void Vehicle::draw(sf::RenderWindow& window)
{
	window.draw(m_rectBox);
}
