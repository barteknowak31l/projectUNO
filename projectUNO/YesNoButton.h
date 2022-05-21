#pragma once
#ifndef YESNOBUTTON_C
#define YESNOBUTTON_C
#include <SFML/Graphics.hpp>
#include "button.h"
#include "gameManager.h"

class YesNoButton : public Button
{
public:
	YesNoButton(sf::Vector2f position, sf::Texture* texture,bool val) : Button(position, texture),value(val) {};
	YesNoButton(const YesNoButton& other) : Button(other) {};
	~YesNoButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;

	bool value;


};
#endif

