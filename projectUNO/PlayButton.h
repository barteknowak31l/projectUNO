#pragma once
#ifndef PLAYBUTTON_C
#define PLAYBUTTON_C

#include <SFML/Graphics.hpp>
#include "button.h"



struct gameManager;


class PlayButton : public Button
{
public:
	PlayButton(sf::Vector2f position, sf::Texture *texture) : Button(position, texture) {};
	PlayButton(const PlayButton& other) : Button(other) {};
	~PlayButton()
	{
		instances.erase(this);
	}

	void onClick(gameManager*) override;



};

#endif // !PLAYBUTTON_C