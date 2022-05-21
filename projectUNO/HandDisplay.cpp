#include "HandDisplay.h"
#include "player.h"


void HandDisplay::refreshHandDisplay(gameManager* gm)
{
	int counter = 0;
	int xPos = xStartPos;
	int yPos = row1Y;


	list* tmp = gm->game->players[gm->game->turn]->hand;
	CardButtonList* tmpButton = cardButtonList;

	//setpos
	while (tmpButton != NULL)
	{
		if (counter % 26 == 0 && counter != 0)
		{
			yPos = yPos + row2Y;
			xPos = xStartPos;
		}

		tmpButton->cardButton->setPos(sf::Vector2f(xPos, yPos));

		xPos = xPos + xOffset;
		tmpButton = tmpButton->next;
		counter++;
	}


	tmpButton = cardButtonList;
	counter = 0;

	while (tmp != NULL)
	{

		tmpButton->cardButton->setSprite(tmp->c->texture);
		tmpButton->cardButton->card = tmp->c;
		tmpButton->cardButton->isActive = true;
		tmpButton = tmpButton->next;
		tmp = tmp->next;

		counter++;
	}



	while (tmpButton != NULL)
	{
		tmpButton->cardButton->isActive = false;

		tmpButton = tmpButton->next;
	}
	

	//for (int i = counter; i < 24; i++)
	//{
	//
	//	tmpButton->cardButton->isActive = false;
	//	
	//	tmpButton = tmpButton->next;

	//}

}

void HandDisplay::refreshHandDisplayLastPlayer(gameManager* gm)
{


	int counter = 0;
	int xPos = xStartPos;
	int yPos = row1Y;
	int index;

	if (getCardValueID(gm->game->cardsPlayed->c->id) == 10)
	{
		index = gm->game->turn - gm->game->playDirection;
		if (index < 0) { index = gm->game->playerCount - 1; }
		if (index > gm->game->playerCount - 1) { index = 0; }
		index = index - gm->game->playDirection;
	}
	else
	{
		index = gm->game->turn - gm->game->playDirection;
	}

	if (index < 0) { index = gm->game->playerCount-1; }
	if (index > gm->game->playerCount-1) { index = 0; }

	if (gm->game->players[index]->comp)
	{
		return;
	}


	list* tmp = gm->game->players[index]->hand;
	CardButtonList* tmpButton = cardButtonList;

	//setpos
	while (tmpButton != NULL)
	{
		if (counter %26 == 0 && counter!=0)
		{
			yPos = yPos + row2Y;
			xPos = xStartPos;
		}

		tmpButton->cardButton->setPos(sf::Vector2f(xPos, yPos));

		xPos = xPos + xOffset;
		tmpButton = tmpButton->next;
		counter++;
	}


	tmpButton = cardButtonList;
	counter = 0;

	while (tmp != NULL)
	{

		tmpButton->cardButton->setSprite(tmp->c->texture);
		tmpButton->cardButton->card = tmp->c;
		tmpButton->cardButton->isActive = true;
		tmpButton = tmpButton->next;
		tmp = tmp->next;

		counter++;
	}



	while (tmpButton != NULL)
	{
			tmpButton->cardButton->isActive = false;

			tmpButton = tmpButton->next;
	}

	//for (int i = counter; i < 24; i++)
	//{

	//	tmpButton->cardButton->isActive = false;

	//	tmpButton = tmpButton->next;

	//}
}

void HandDisplay::createCardButtons(gameManager* gm)
{
	cardButtonList = createCardButtonList();


	CardButton* tmp;
	sf::Texture* t = gm->textures->cardTextures->blackColor;
	for (int i = 0; i < 108; i++) //24 
	{
		tmp = new CardButton(sf::Vector2f(0, 0), t,108-i);
		cardButtonListAppend(&cardButtonList, tmp);
	}


}

CardButtonList* createCardButtonList()
{
	CardButtonList* l = NULL;
	return l;
}

CardButton* cardButtonListAppend(CardButtonList** head, CardButton* button)
{
	if (*head == NULL)
	{
		*head = (CardButtonList*)malloc(sizeof(CardButtonList));
		(*head)->cardButton = button;
		(*head)->next = NULL;
	}
	else
	{
		CardButtonList* newItem = (CardButtonList*)malloc(sizeof(CardButtonList));
		newItem->cardButton = button;
		newItem->next = *head;
		(*head) = newItem;
	}

	return button;
}