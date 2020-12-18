// Author: Mitch Barnett
// Created: April 2016

#include "TrafficLane.h"


// Constructor sets the values of member variables
TrafficLane::TrafficLane(float fXpos, float fYpos, float fWidth, float fSpeed, std::vector<sf::Texture*> aptexTextures)
{
	m_fLaneHeight = fYpos;
	m_fLaneXStart = fXpos;
	m_fWidth = fWidth;
	m_fLaneSpeed = fSpeed;
	m_vptexTextures = aptexTextures;
	m_fNextSpawn = 0;

	//initaly populate lanes
	// Do until edge of screen
	for (int i = 0; i < 800; i += (int)m_fWidth + rand() % (250 - 50 + 1) + 50)
	{
		m_vCarsInLane.push_back(Vehicle(m_fLaneSpeed, (float)i, m_fLaneHeight, m_fWidth, m_vptexTextures));
	}
}

// draws each car in the lane
void TrafficLane::draw(sf::RenderWindow& window)
{
	// Calls the draw function for each vehicle in the vector
	for (unsigned int i = 0; i < m_vCarsInLane.size(); i++){
		(m_vCarsInLane[i]).draw(window);
	}
}

// updates the position each car in the lane
void TrafficLane::update(float elapsed, float fGameTime)
{
	// Calls the update function for each vehicle in the lane
	for (unsigned int i = 0; i < m_vCarsInLane.size(); i++){
		m_vCarsInLane[i].update(elapsed);
	}

	// time since last car was added to lane
	m_fTimeSinceSpawn = m_spawnClock.getElapsedTime().asSeconds();

	// If the time scince the last spawn is greater than the time needed for the next spawn then spawn a car
	if (m_fTimeSinceSpawn > m_fNextSpawn ){
		m_vCarsInLane.push_back(Vehicle(m_fLaneSpeed, m_fLaneXStart, m_fLaneHeight, m_fWidth, m_vptexTextures));
		m_spawnClock.restart();
		m_fNextSpawn = getNextSpawn();
	}

	// if ther is more than 10 cars in the lane then remove the earliest car to have spawned
	if (m_vCarsInLane.size() > 10)
	{
		m_vCarsInLane.erase(m_vCarsInLane.begin());
	}
}

// Get the time needed to pass for the next vehicle to spawn
float TrafficLane::getNextSpawn()
{
	float fTempLaneSpeed;
	// turning speed to always be positve
	if (m_fLaneSpeed < 0)
	{
		fTempLaneSpeed = -m_fLaneSpeed;
	}else{
		fTempLaneSpeed = m_fLaneSpeed;
	}
	
	float fMinTime; 	// Minimum time for a car to spawn
	float fMaxTime;		// Maximum time for a car to spawn
	fMinTime = (m_fWidth + 50 ) / fTempLaneSpeed;		// Distance of a vehicle plus size of the player
	fMaxTime = (m_fWidth  + 50 )/ fTempLaneSpeed * 3;	// Distance of 3 vehicles plus the size of the player
	return (fMinTime + (float) (rand()) / ( (float) (RAND_MAX / (fMaxTime - fMinTime)))); //Return a float between the min and max times
}

// Check for a collision
bool TrafficLane::checkCollision(sf::FloatRect other)
{
	// Call checkCollision for each vechicle in the lane
	for (unsigned int i = 0; i < m_vCarsInLane.size(); i++){
		if (m_vCarsInLane[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}
