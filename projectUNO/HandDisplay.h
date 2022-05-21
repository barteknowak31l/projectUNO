#pragma once
#ifndef HANDDISPLAY_C
#define HANDDISPLAY_C

#include <SFML/Graphics.hpp>
#include "CardButton.h"


#include "gameManager.h"


struct CardButtonList
{
	CardButton* cardButton;
	CardButtonList* next;
};

CardButtonList* createCardButtonList();
CardButton* cardButtonListAppend(CardButtonList** head, CardButton* button);


class HandDisplay
{

public:
	HandDisplay(int y1, int y2, int xStart, int xOff) { row1Y = y1; row2Y = y2; xStartPos = xStart; xOffset = xOff; cardButtonList = NULL; }
	~HandDisplay();

	sf::RectangleShape* bg;

	int row1Y;
	int row2Y;
	
	int xStartPos;
	int xOffset;


	CardButtonList* cardButtonList;

	void createCardButtons(gameManager*);

	void refreshHandDisplay(gameManager* gm);
	void refreshHandDisplayLastPlayer(gameManager* gm);


};
#endif
