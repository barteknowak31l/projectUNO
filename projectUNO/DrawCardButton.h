#pragma once
#ifndef DRAWCARDBUTTON_C
#define DRAWCARDBUTTON_C

#include <SFML/graphics.hpp>
#include "gameManager.h"
#include "button.h"
#include "player.h"

class DrawCardButton : public Button
{
public:
	DrawCardButton(sf::Vector2f position, sf::Texture* texture) : Button(position, texture) {};
	DrawCardButton(const DrawCardButton& other) : Button(other) {};
	~DrawCardButton()
	{
		instances.erase(this);
	}

	void onClick(gameManager*) override;

	void setHover() { hovered = true; }
	void unsetHover() { hovered = false; }

	void setPressed() { pressed = true; };
	void unsetPressed() { pressed = false; }

};
#endif
