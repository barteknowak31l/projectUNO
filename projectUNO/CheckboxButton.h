#pragma once
#ifndef CHECKBOXBUTTON_C
#define CHECKBOXBUTTON_C
#include <SFML/Graphics.hpp>
#include "button.h"

class CheckboxButton : public Button
{
public:
	CheckboxButton(sf::Vector2f position, sf::Texture* texture,int* val) : Button(position, texture),value(val) {};
	CheckboxButton(const CheckboxButton& other) : Button(other),value(other.value) {};
	~CheckboxButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;

	int* value;

};
#endif
