#pragma once
#ifndef INCREMENTBUTTON_C
#define INCREMENTBUTTON_C

#include <SFML/Graphics.hpp>
#include "button.h"


class IncrementButton : public Button
{
public:
	IncrementButton(sf::Vector2f position, sf::Texture* texture, int mi, int ma, int st, int* val) : Button(position, texture), min(mi), max(ma), step(st),value(val) {};
	IncrementButton(const IncrementButton& other) : Button(other), min(other.min),max(other.max),step(other.step),value(other.value) {};
	~IncrementButton()
	{
		instances.erase(this);
	}
	void onClick(gameManager*) override;

	int step;

	int min, max;
	int *value;


};

#endif // !INCREMENTBUTTON_C