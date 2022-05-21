#pragma once
#ifndef TOPCARD_C
#define TOPCARD_C

#include <SFML/Graphics.hpp>
#include "gameManager.h"
#include "cards.h"


class TopCard :  sf::Drawable
{
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;

public:
	TopCard(sf::Vector2f position) { sprite.setPosition(position); };
	~TopCard() {};

	sf::Sprite sprite;
	void refreshTopCard(gameManager* gm);
 
};
#endif // !TOPCARD_C
