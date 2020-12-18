// Author: Mitch Barnett
// Created: April 2016

#ifndef TrafficLane_H
#define TrafficLane_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Vehicle.h"


class TrafficLane
{
public:
	// Constructor
	TrafficLane(float fXpos, float fYpos, float fWidth, float fSpeed, std::vector<sf::Texture*> aptexTextures); 
	// returns the time that should pass unitl the next vehicle should spawn
	float getNextSpawn();
	//Check if amy of the vehicles have collided
	bool checkCollision(sf::FloatRect other);
	// Upodates the position of vehicles in the lane
	void update(float elapsed, float fGameTime);
	// Draws the vehicles to the screen
	void draw(sf::RenderWindow& window);
		

private:
	float m_fLaneHeight;		// The lane height on the screen
	float m_fLaneXStart;		// The start position of the vehicles in this lane
	float m_fNextSpawn;			// How long after the last spawn the next vehicle should spawn
	float m_fWidth;				// The width of the vehicles in the lane
	float m_fTimeSinceSpawn;	// How much time has passes scince the last vehicle spann
	float m_fLaneSpeed;			// The speed of the vehicles in the lane
	char m_cDirection;			// should be 'f' or 'r' for forwards or reverse	

	std::vector<Vehicle> m_vCarsInLane;				// Holds all the vehicles on the current lane
	sf::Clock m_spawnClock;							// Clock holds how much time has passed scince the last spawn
	sf::Clock m_laneClock;							// Tracks how
	std::vector<sf::Texture*> m_vptexTextures;
};
#endif
