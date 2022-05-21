#pragma once
#ifndef TEXTBUTTON_C
#define TEXTBUTTON_C
#include "gameManager.h"
#include "button.h"
#include <sstream>

class TextButton : public Button
{
protected:


public:
	
	TextButton(sf::Vector2f position, sf::Texture* texture, int i) : Button(position, texture), id(i) {};
	TextButton(const TextButton& other) : Button(other) {};
	~TextButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;


	void textInput(gameManager* gm, sf::Event& event);

	

	std::ostringstream text;
	sf::Text textBox;
	int id;
	int limit = 7;

	void inputLogic(int charTyped);

	void deleteLastChar();

	void setFont(sf::Font font);

	void setPosition(sf::Vector2f pos);

	void setColor(sf::Color col) { textBox.setFillColor(col); }

	std::string getText()
	{
		return text.str();
	}

	void typedOn(sf::Event event);


	



};
#endif

