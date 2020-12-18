// Author: Mitch Barnett
// Created: April 2016

#include "Background.h"

// Initialises all elements all elements of the background and positions them
Background::Background()
{
	// Set the size of the background elements
	m_rectTopPavement.setSize(sf::Vector2f(900.0f, 50.0f));
	m_rectCentralRes.setSize(sf::Vector2f(900.0f, 50.0f));
	m_rectBottomPavement.setSize(sf::Vector2f(900.0f, 50.0f));
	m_rectTopRoad.setSize(sf::Vector2f(900.0f, 250.0f));
	m_rectBottomRoad.setSize(sf::Vector2f(900.0f, 250.0f));
	// Set the position of the background elelments
	m_rectCentralRes.setPosition(sf::Vector2f(0.0f, 300.0f));
	m_rectBottomPavement.setPosition(sf::Vector2f(0.0f, 600.0f));
	m_rectTopRoad.setPosition(sf::Vector2f(0, 50));
	m_rectBottomRoad.setPosition(sf::Vector2f(0, 350));

	loadTextures();
}

// Loads textures onto the background elelments
void Background::loadTextures()
{
	m_texTopPavement.loadFromFile("assets/textures/background/Pavement_top.png");
	m_texCentralRes.loadFromFile("assets/textures/background/CenteralRes.png");
	m_texBottomPavement.loadFromFile("assets/textures/background/Pavement_bottom.png");
	m_texRoad.loadFromFile("assets/textures/background/Road.png");

	m_rectTopPavement.setTexture(&m_texTopPavement);
	m_rectCentralRes.setTexture(&m_texCentralRes);
	m_rectBottomPavement.setTexture(&m_texBottomPavement);
	m_rectTopRoad.setTexture(&m_texRoad);
	m_rectBottomRoad.setTexture(&m_texRoad);
}

// Draws the elements of the background to the supplied window
void Background::draw(sf::RenderWindow& window)
{
	window.draw(m_rectTopPavement);
	window.draw(m_rectCentralRes);
	window.draw(m_rectBottomPavement);
	window.draw(m_rectTopRoad);
	window.draw(m_rectBottomRoad);
}