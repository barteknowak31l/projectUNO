#pragma once
#ifndef EXITBUTTON_H
#define EXITBUTTON_H

#include <SFML/graphics.hpp>
#include "button.h"


class ExitButton : public Button
{
public:
	ExitButton(sf::Vector2f position, sf::Texture* texture) : Button(position, texture) {};
	ExitButton(const ExitButton& other) : Button(other) {};
	~ExitButton()
	{
		instances.erase(this);
	}

	void onClick(gameManager*) override;

	void setHover() { hovered = true; }
	void unsetHover() { hovered = false; }

	void setPressed() { pressed = true; };
	void unsetPressed() { pressed = false; }

};




#endif // !EXITBUTTON_H