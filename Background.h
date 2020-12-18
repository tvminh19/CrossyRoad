// Author: Mitch Barnett
// Created: April 2016

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>

//Creates the background for the game
class Background
{
public:
	Background(); //Constructor
	void draw(sf::RenderWindow& window); // Draws the background to the supplied window

	sf::RectangleShape m_rectTopPavement; // Public so the bounds can be checked
private:
	void loadTextures();	// Loads the textures onto the game objects

	// The elements that make up the background
	sf::RectangleShape m_rectTopRoad;
	sf::RectangleShape m_rectBottomRoad;
	sf::RectangleShape m_rectCentralRes;
	sf::RectangleShape m_rectBottomPavement;
	// The textures that will be applied to the background elements
	sf::Texture m_texRoad;
	sf::Texture m_texTopPavement;
	sf::Texture m_texCentralRes;
	sf::Texture m_texBottomPavement;
};
#endif
