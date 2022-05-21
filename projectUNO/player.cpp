#include "player.h"
#include <string>

#include "scene.h"

using namespace std;

player* createPlayer(int id,bool comp,std::string n)
{
	player* p = (player*)malloc(sizeof(player));
	p->id = id;
	p->hand = createList();
	p->uno = 0;
	p->comp = comp;

	p->name = new sf::String;

	

	*p->name = n;

	return p;
}

void deletePlayer(player* p)
{
	destroyList(&p->hand);
	free(p);

}

#pragma region LISTA
list* createList()
{
	list* l = NULL;
	return l;
}

void destroyList(list** s)
{
	list* tmp = *s;
	list* previous = NULL;
	while (tmp != NULL)
	{
		if (previous != NULL)
		{
			free(previous);
		}
		previous = tmp;
		tmp = tmp->next;
	}

}

card* listAppend(list** head, card* c)
{
	if (*head == NULL)
	{
		*head = (list*)malloc(sizeof(list));
		(*head)->c = c;
		(*head)->next = NULL;
	}
	else
	{
		list* newItem = (list*)malloc(sizeof(list));
		newItem->c = c;
		newItem->next = *head;
		(*head) = newItem;
	}

	return c;
}

card* deleteFromList(list** head, card* c)
{
	if (*head == NULL)
	{
		printf("player::deleteFromList : error - list is empty\n");
		//exit(1);

		return c;
	}

	card* deleted = c;
	list* current = *head;
	list* prev = NULL;


	if (current != NULL && current->c->id == c->id)
	{
		*head = current->next;
		deleted = current->c;
		free(current);
		return deleted;
	}

	while (current != NULL)
	{
		if (current->c->id == c->id)
		{
			deleted = current->c;
			prev->next = current->next;
			free(current);
			return deleted;
		}
		prev = current;
		current = current->next;

	}



	//printf("--- player::deleteFromList : error - item %d not found and couldn't be deleted\n", c->id);
	return deleted;


}

void showHand(game* g)
{
	list* head = g->players[g->turn]->hand;

	list* current = head;
	printf("player %d HAND:\n", g->players[g->turn]->id);

	int num = 1;
	while (current != NULL)
	{
		printf("%d.", num++);
		getCardFromId(current->c->id);
		current = current->next;
	}

}

int listSize(list* l)
{
	int counter = 0;
	list* current = l;

	while (current != NULL)
	{
		counter++;
		current = current->next;
	}

	return counter;
}

void deleteFromListById(list** head, int id)
{
	if (*head == NULL)
	{
		printf("player::deleteFromListByID : error - list is empty\n");
		//exit(1);
		return ;
	}

	list* current = *head;

	if (current != NULL && current->c->id == id)
	{
		*head = current->next;
		free(current);
		return ;
	}

	list* prev = createList();
	while (current != NULL)
	{

		if (current->c->id == id)
		{
			prev->next = current->next;
			free(current);
			return;
		}
		prev = current;
		current = current->next;

	}
	printf("--- player::deleteFromListID : error - item %d not found and couldn't be deleted\n", id);
	return ;


}

list* listCopy(list** head)
{
	list* newList = createList();

	list* tmp = *head;

	while (tmp != NULL)
	{
		listAppend(&newList,tmp->c);
		tmp = tmp->next;
	}

	reverseList(&newList);

	return newList;
}

void listShuffle(list** head)
{
	if (*head == NULL)
	{
		printf("cards::shuffle: error - stack is empty\n");
		return;
	}

	int deckSize = listSize(*head);

	//zdejmij ze stosu i dodaj do listy
	int* positions = (int*)malloc(deckSize * sizeof(int));
	card** temp = (card**)malloc(deckSize * sizeof(card*));


	for (int i = 0; i < deckSize; i++)
	{
		positions[i] = i;
		temp[i] = deleteFromList(head,(*head)->c);
	}


	//wymieszaj positions
	int j = 0;
	for (int i = deckSize - 2; i > 0; i--)
	{
		j = randomInt(0, i);
		int tmp = positions[i + 1];
		positions[i + 1] = positions[j];
		positions[j] = tmp;
	}

	*head = createList();

	//poloz na stosie   
	for (int i = 0; i < deckSize; i++)
	{
		listAppend(head, temp[positions[i]]);
	}

}

void reverseList(list** head)
{
	int siz = listSize(*head);
	list* temp = createList();

	for (int i = 0; i < siz; i++)
	{
		listAppend(&temp, deleteFromList(head, (*head)->c));
	}
	free(*head);

	*head = temp;
}

void showList(list* head)
{

	list* current = head;

	int num = 1;
	while (current != NULL)
	{
		printf("%d.", num++);
		getCardFromId(current->c->id);
		current = current->next;
	}


}

void sortList(list* head)
{
	list* tmp = NULL;
	list* node = NULL;
	card* tmpCard;

	node = head;

	while (node != NULL)
	{
		tmp = node;
		while(tmp->next != NULL)
		{
			if (tmp->c->id > tmp->next->c->id)
			{
				tmpCard = tmp->c;
				tmp->c = tmp->next->c;
				tmp->next->c = tmpCard;
			}
			tmp = tmp->next;
		}
		node = node->next;
	}
}

bool listEmpty(list* head)
{
	return head == NULL;
}

#pragma endregion

#pragma region KARTY
card* drawCard(game* g,int playerId)
{
	if (empty(g->deck))
	{
		printf("player::drawCard : error - deck is empty\n");
		return NULL;
	}

	card* c = pop(&g->deck);
	printf("---player %d draw ", g->players[playerId]->id);
	getCardFromId(c->id);
	listAppend(&g->players[playerId]->hand, c);

	if (g->gameStarted && playerId == g->turn)
	{
		if (checkCardCorrect(c,g->cardsPlayed) || isBlackCard(c) ) {

			if (g->players[g->turn]->comp == 0)
			{
				;

			}
			else {

				if (!isBlackCard(c))
				{
					playCard(g, 1);
					return c;
				}



			}


		}
	}

	if (g->players[g->turn]->comp)
	{
		g->players[g->turn]->compDidAnAction = true;
	}
	else if(g->players[g->turn]->comp == 0 && !(checkCardCorrect(c, g->cardsPlayed) || isBlackCard(c)))
	{
		printf("sortuje liste %d z draw\n", playerId);
		sortList(g->players[playerId]->hand);
		g->gm->sceneManager->gameUI->player0cards->setString("Cards: " + to_string(listSize(g->players[playerId]->hand)));
	}

	g->players[g->turn]->uno = 0;

	return c;

}

void playCard(game* g, int position)
{
	list** hand = &g->players[g->turn]->hand;

	if (position > listSize(*hand))
	{
		printf("player::playCard : error - no such card to play\n");
		return;
	}

	int counter = 1;
	list* current = *hand;

	while (counter != position)
	{
		current = current->next;
		counter++;
	}

	bool black = isBlackCard(current->c);

	//zagrywanie karty
	if (checkCardCorrect(current->c, g->cardsPlayed) || black)
	{
		;
	}
	else
	{
		printf("player::PlayCard : error - card do not match the top card!\n");
		return;
	}

	isCardSpecial(g, current->c);

	printf("player %d played: ", g->players[g->turn]->id);
	getCardFromId(current->c->id);
	push(&g->cardsPlayed,deleteFromList(hand, current->c));
	
	if (listSize(g->players[g->turn]->hand) == 1)
	{
		uno(g);
	}

	g->gm->sceneManager->gameUI->player0cards->setString("Cards: " + to_string(listSize(g->players[g->turn]->hand)));

	if (g->players[g->turn]->comp == false)
	{
		printf("sortuje liste %d z play\n", g->turn);
		sortList(g->players[g->turn]->hand);

		nextTurn(g);
		if (g->skipTurn)
		{
			nextTurn(g);
			g->skipTurn = 0;
		}
	}
	else
	{
		g->players[g->turn]->compDidAnAction = true;
	}


}

int checkCardCorrect(card* cardToPlay, stack* topCard)
{


	int topId = topCard->c->id;
	int ctpId = cardToPlay->id;

	int topValue = 15;
	topValue = topValue & topId;

	int ctpValue = 15;
	ctpValue = ctpValue & ctpId;

	int topColor = 48;
	topColor = topColor & topId;

	int ctpColor = 48;
	ctpColor = ctpColor & ctpId;


	if (topColor == ctpColor || topValue == ctpValue)
	{
		return 1;
	}

	return 0;
}

#pragma endregion

void uno(game* g)
{
	printf("player %d: UNO!", g->players[g->turn]->id);
	g->players[g->turn]->uno = 1;
}

void AiPlayBlackCard(game* g,int pos)
{

	int colors[4]; //R B G Y
	colors[0] = 0;
	colors[1] = 0;
	colors[2] = 0;
	colors[3] = 0;

	int colormask = 48;
	int colorValue = 0;

	list* tmp = g->players[g->turn]->hand;

	//policz karty o danym kolorze
	while (tmp != NULL)
	{
		if (!isBlackCard(tmp->c))
		{
			colorValue = tmp->c->id & colormask;
			colorValue = colorValue >> 4;

			colors[colorValue]++;
		}
		tmp = tmp->next;
	}

	int maximum = -1;
	int maxColor;


	for (int i = 0; i < 4; i++)
	{	
		if (colors[i] > maximum)
		{
			maximum = colors[i];
			maxColor = i;
		}
	}


	//zagraj karte i zmien kolor na wybrany
	list** hand = &g->players[g->turn]->hand;

	if (pos > listSize(*hand))
	{
		printf("player::playCard : error - no such card to play\n");
		return;
	}

	int counter = 1;
	list* current = *hand;
	while (counter != pos)
	{
		current = current->next;
		counter++;
	}

	bool black = isBlackCard(current->c);

	//zagrywanie karty
	if (checkCardCorrect(current->c, g->cardsPlayed) || black)
	{
		;
	}
	else
	{
		printf("player::PlayCard : error - card do not match the top card!\n");
		return;
	}

	//changeCol
	if (current->c->id == 13)
	{
		AiSpecialChangeColor(g, current->c, maxColor);

	}

	//changeCol +4
	if (current->c->id == 14)
	{
		AiSpecialChangeColorDraw4(g, current->c,maxColor);
	}




	printf("player %d played: ", g->players[g->turn]->id);
	getCardFromId(current->c->id);
	push(&g->cardsPlayed, deleteFromList(hand, current->c));


	g->gm->sceneManager->gameUI->player0cards->setString("Cards: " + to_string(listSize(g->players[g->turn]->hand)));

	if (listSize(g->players[g->turn]->hand) == 1)
	{
		uno(g);
	}

	g->players[g->turn]->compDidAnAction = true;

}


