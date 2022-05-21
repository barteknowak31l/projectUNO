#pragma once

#ifndef CARDBUTTON_C
#define CARDBUTTON_C

#include <SFML/Graphics.hpp>
#include "button.h"
#include "cards.h"


class CardButton : public Button
{
public:
	CardButton(sf::Vector2f post, sf::Texture* texture,int pos) : Button(post, texture),position(pos) {};
	CardButton(const CardButton& other) : Button(other) {};
	~CardButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;

	card* card;
	int position;


};
#endif
