// Author: Mitch Barnett
// Created: April 2016

#ifndef TRAFFICMANAGER_H
#define TRAFFICMANAGER_H

#include "TrafficLane.h"

class TrafficManager
{
public:
	// Constructor
	TrafficManager();

	// Destructor
	~TrafficManager();

	// Loads the .png of vehicles into 3 arrays of sf::Texture objects depending on their speed
	void loadTextures();

	void unloadTextures();

	// updates all traffic objects position
	void update(float elapsed, float fGameTime);

	// Draws all traffic objects to the passed window
	void draw(sf::RenderWindow& window);

	// Returns true if any traffic object collides with the passed FloatRect
	bool checkCollision(sf::FloatRect other);

private:
	// A vector containing pointers to the textures
	std::vector<sf::Texture*> m_vptexFastVehicleTextures;
	std::vector<sf::Texture*> m_vptexMediumVehicleTextures;
	std::vector<sf::Texture*> m_vptexSlowVehicleTextures;

	// A vector to hold the traffic lanes
	std::vector<TrafficLane> m_vLanes;

};

#endif