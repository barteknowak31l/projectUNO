#pragma once
#ifndef CHOOSECOLORBUTTON_C
#define CHOOSECOLORBUTTON_C
#include <SFML/Graphics.hpp>
#include "button.h"
#include "cards.h"
#include "gameManager.h"

class ChooseColorButton : public Button
{
public:
	ChooseColorButton(sf::Vector2f post, sf::Texture* texture, int col) : Button(post, texture), color(col) {};
	ChooseColorButton(const ChooseColorButton& other) : Button(other) {};
	~ChooseColorButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;

	card* card;
	int color;
};

#endif
