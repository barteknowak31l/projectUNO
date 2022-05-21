#include "TextButton.h"
#include <string>





void TextButton::onClick(gameManager* gm)
{
	isClicked=true;
}

void TextButton::inputLogic(int charTyped)
{
	if (charTyped != 8)
	{
		text << static_cast<char>(charTyped);
	}
	else
	{
		if (text.str().length() > 0)
		{
			deleteLastChar();
		}
	}

	textBox.setString(text.str());
}

void TextButton::deleteLastChar()
{
	std::string t = text.str();
	std::string newT = "";

	for (int i = 0; i < t.length() - 1; i++)
	{
		newT += t[i];
	}

	text.str("");
	text << newT;	

	textBox.setString(text.str());


}


void TextButton::setFont(sf::Font font)
{
	textBox.setFont(font);
}

void TextButton::setPosition(sf::Vector2f pos)
{
	textBox.setPosition(pos);
}

void TextButton::typedOn(sf::Event input)
{
	if (isClicked)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (text.str().length() <= limit)
			{
				inputLogic(charTyped);
			}
			else if (text.str().length() > limit && charTyped == 8)
			{
				deleteLastChar();
			}
		}
	}
}
