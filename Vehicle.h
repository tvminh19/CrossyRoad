// Author: Mitch Barnett
// Created: April 2016

#ifndef VEHICLE_H
#define VEHICLE_H

#include "Movable.h"
#include <SFML/Graphics.hpp>



class Vehicle : public Movable
{
public:
	// Constructor initialises values
	Vehicle(float fSpeed, float fXPos, float dYPos, float fWidth, std::vector<sf::Texture*> vptexTextures); 
	// Sets a new speed for traffic int he lane
	void setSpeed(float speed);
	// Updates each vehicle in the lane
	void update(float elapsed);
	// Draws each vehicle in the lane to the provided screen
	void draw(sf::RenderWindow& window);
private:
	float m_fX;			// X postion of the vehicle
	float m_fY;			// Y postion of the vehicle
	float m_fSpeed;		// Speed of the vehicle on the x axis
	float m_fLength;	// length of the vehicle	
	float m_fWidth;		// width of the vehicle
};

#endif
