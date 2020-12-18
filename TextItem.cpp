// Author: Mitch Barnett
// Created: April 2016

#include "TextItem.h"
#include <iostream>
#include <iomanip> // for setting precision

// Creates a text object to display a string
void TextItem::setTextItem(std::string textString, sf::Vector2f vec2Position, int iSize)
{
	// Set the font
	m_font.loadFromFile("assets/fonts/arial.ttf");
	m_text.setFont(m_font);

	m_text.setString(textString);		// set the string to display
	m_text.setCharacterSize(iSize);		// set the character size
	m_text.setColor(sf::Color::White);	// set the color
	m_text.setPosition(vec2Position);		// Set the position
}

// Creates a text object to display a string and int value
void TextItem::setTextItem(std::string textString, int iValue, sf::Vector2f vec2Position)
{
	// Set the font
	m_font.loadFromFile("assets/fonts/arial.ttf");
	m_text.setFont(m_font); 

	m_textStream << textString << iValue;		// Adds the string and value to the textStream
	std::string sString(m_textStream.str());	// Make a string from the contents of the textStream
	m_text.setString(sString);					// Set the text object to display the string
	m_textStream.str("");						// Clears the text stream

	m_text.setCharacterSize(22);		// set the character size
	m_text.setColor(sf::Color::White);	// set the color
	m_text.setPosition(vec2Position);	// Set the position
}

// Creates a text object to display a string  and float value
void TextItem::setTextItem(std::string textString, float fValue, sf::Vector2f vec2Position)
{
	// Set the font
	m_font.loadFromFile("assets/fonts/arial.ttf");
	m_text.setFont(m_font);

	m_textStream << textString << std::fixed << std::setprecision(2) << fValue;		// Add the string and value to the textStream
	std::string sString(m_textStream.str());	// Make a string from the contents of the textStream
	m_text.setString(sString);					// Set the text object to display the string
	m_textStream.str("");						// Clears the text stream

	m_text.setCharacterSize(22);		// set the character size
	m_text.setColor(sf::Color::White);	// set the color
	m_text.setPosition(vec2Position);	// Set the position
}

// Updates a text item with a int value
void TextItem::update(std::string textString, int iValue)
{
	m_textStream << textString << iValue;		// Add the string and value to the textStream
	std::string newString(m_textStream.str());	// Make a string from the contents of the textStream
	m_text.setString(newString);				// Set the text object to display the string
	m_textStream.str("");						// Clears the text stream
}

// Updates a text item with a float value
void TextItem::update(std::string textString, float fValue)
{
	m_textStream << textString << std::fixed << std::setprecision(2) << fValue;		// Add the string and value to the textStream
	std::string newString(m_textStream.str());	// Make a string from the contents of the textStream
	m_text.setString(newString);				// Set the text object to display the string
	m_textStream.str("");						// Clears the text stream
}

// Draws the text item to the supplied window
void TextItem::draw(sf::RenderWindow& window)
{
	window.draw(m_text);
}
