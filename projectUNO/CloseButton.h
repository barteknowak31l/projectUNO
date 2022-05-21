#pragma once
#ifndef CLOSEBUTTON_C
#define CLOSEBUTTON_C

#include <SFML/Graphics.hpp>
#include "button.h"

class CloseButton : public Button
{
public:
	CloseButton(sf::Vector2f post, sf::Texture* texture) : Button(post, texture) {};
	CloseButton(const CloseButton& other) : Button(other) {};
	~CloseButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;


};
#endif

