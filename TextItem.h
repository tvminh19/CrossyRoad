// Author: Mitch Barnett
// Created: April 2016

#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

// Creates a text UI item
// Can be just a string or a string and a value to display
class TextItem
{
public:
	// Constructor for displaying a string at a given posision with a given size
	TextItem(std::string textString, sf::Vector2f vec2Position, int iSize); 
	// Constructor for displaying a string label and a int value
	TextItem(std::string textString, int iValue, sf::Vector2f vec2Position); 
	// Constructor for displaying a string label and a float value
	TextItem(std::string textString, float fValue, sf::Vector2f vec2Position); 

	// Update function to update the values
	void update(std::string textString, int iValue);
	void update(std::string textString, float fValue);

	// Draws the text to the given window
	void draw(sf::RenderWindow& window);

private:
	sf::Text m_text;					// The text object	
	std::ostringstream m_textStream;	// Holds the string and its value
	sf::Font m_font;					// Contains the texts font	
};

#endif


