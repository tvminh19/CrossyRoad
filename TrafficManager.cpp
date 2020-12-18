// Author: Mitch Barnett
// Created: April 2016


#include "TrafficManager.h"
#include <SFML/Graphics.hpp>
#include <string>

// Constructor Initialises all the traffic lanes 
// A total of 10 lanes of trafic with inside lanes moving fastest
TrafficManager::TrafficManager()
{
	loadTextures();
	m_vLanes.push_back(TrafficLane(-150, 50, 150, 70, m_vptexSlowVehicleTextures));
	m_vLanes.push_back(TrafficLane(-150, 100, 150, 80, m_vptexSlowVehicleTextures));
	m_vLanes.push_back(TrafficLane(-100, 150, 100, 100, m_vptexMediumVehicleTextures));
	m_vLanes.push_back(TrafficLane(-100, 200, 100, 120, m_vptexMediumVehicleTextures));
	m_vLanes.push_back(TrafficLane(-100, 250, 100, 140, m_vptexFastVehicleTextures));
	m_vLanes.push_back(TrafficLane(900, 350, 100, -140, m_vptexFastVehicleTextures));
	m_vLanes.push_back(TrafficLane(900, 400, 100, -120, m_vptexMediumVehicleTextures));
	m_vLanes.push_back(TrafficLane(900, 450, 100, -100, m_vptexMediumVehicleTextures));
	m_vLanes.push_back(TrafficLane(950, 500, 150, -80, m_vptexSlowVehicleTextures));
	m_vLanes.push_back(TrafficLane(950, 550, 150, -70, m_vptexSlowVehicleTextures));
}

// Destructor frees memory used by the textures
TrafficManager::~TrafficManager()
{
	unloadTextures();
}

// Calls each lanes update function to update the traffics position
void TrafficManager::update(float fElapsed, float fGameTime)
{
	for (int i = 0; i < 10; i++){
		m_vLanes[i].update(fElapsed, fGameTime);
	}
}

// Calls each lanes draw function to draw the traffic on the supplied window
void TrafficManager::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < 10; i++){
		m_vLanes[i].draw(window);
	}
}

// Checks for a collision in each lane
bool TrafficManager::checkCollision(sf::FloatRect other)
{
	for (int i = 0; i < 10; i++){
		if (m_vLanes[i].checkCollision(other))
		{
			return true;	// collision
		}
	}
	return false;	// no collision
}

void TrafficManager::loadTextures()
{
	// Set values for size of the arrays
	const int kiFastFiles = 10;
	const int kiMediumFiles = 9;
	const int kiSlowFiles = 3;

	// List of textures files for fast vehicles 
	std::string asFastFiles[kiFastFiles] =
	{
		"assets/textures/vehicles/fast/AudiBlue.png",
		"assets/textures/vehicles/fast/AudiGreen.png",
		"assets/textures/vehicles/fast/AudiPurple.png",
		"assets/textures/vehicles/fast/AudiRed.png",
		"assets/textures/vehicles/fast/AudiYellow.png",
		"assets/textures/vehicles/fast/ViperBlackOrange.png",
		"assets/textures/vehicles/fast/ViperBlackRed.png",
		"assets/textures/vehicles/fast/ViperBlackWhite.png",
		"assets/textures/vehicles/fast/ViperWhiteBlack.png",
		"assets/textures/vehicles/fast/Police.png"
	};
	// List of texture files for medium vehicles 	
	std::string asMediumFiles[kiMediumFiles] =
	{
		"assets/textures/vehicles/medium/CarBlue.png",
		"assets/textures/vehicles/medium/CarGreen.png",
		"assets/textures/vehicles/medium/CarOrange.png",
		"assets/textures/vehicles/medium/CarRed.png",
		"assets/textures/vehicles/medium/CarYellow.png",
		"assets/textures//vehicles/medium/PickupBlue.png",
		"assets/textures/vehicles/medium/PickupGreen.png",
		"assets/textures/vehicles/medium/PickupRed.png",
		"assets/textures/vehicles/medium/Taxi.png"
	};
	// List of texture files for slow vehicles 	
	std::string asSlowFiles[kiSlowFiles] =
	{
		"assets/textures/vehicles/slow/Ambulance.png",
		"assets/textures/vehicles/slow/Truck.png",
		"assets/textures/vehicles/slow/Van.png"
	};

	// for each texture file push a new texture pointer into a vector
	// and load the texture file into it
	for (int i = 0; i < kiFastFiles; i++)
	{
		m_vptexFastVehicleTextures.push_back(new sf::Texture);
		m_vptexFastVehicleTextures[i]->loadFromFile(asFastFiles[i]);
	}

	// for each texture file push a new texture pointer into a vector
	// and load the texture file into it
	for (int i = 0; i < kiMediumFiles; i++)
	{
		m_vptexMediumVehicleTextures.push_back(new sf::Texture);
		m_vptexMediumVehicleTextures[i]->loadFromFile(asMediumFiles[i]);
	}

	// for each texture file push a new texture pointer into a vector
	// and load the texture file into it
	for (int i = 0; i < kiSlowFiles; i++)
	{
		m_vptexSlowVehicleTextures.push_back(new sf::Texture);
		m_vptexSlowVehicleTextures[i]->loadFromFile(asSlowFiles[i]);
	}
}

// frees the memory from the texture pointers
void TrafficManager::unloadTextures()
{
	// for each texture pointer in the vector delete and set to null pointer
	for (unsigned int i = 0; i < m_vptexFastVehicleTextures.size(); i++)
	{
		delete m_vptexFastVehicleTextures[i];
		m_vptexFastVehicleTextures[i] = nullptr;
	}

	// for each texture pointer in the vector delete and set to null pointer
	for (unsigned int i = 0; i < m_vptexMediumVehicleTextures.size(); i++)
	{
		delete m_vptexMediumVehicleTextures[i];
		m_vptexMediumVehicleTextures[i] = nullptr;
	}

	// for each texture pointer in the vector delete and set to null pointer
	for (unsigned int i = 0; i < m_vptexSlowVehicleTextures.size(); i++)
	{
		delete m_vptexSlowVehicleTextures[i];
		m_vptexSlowVehicleTextures[i] = nullptr;
	}
}
