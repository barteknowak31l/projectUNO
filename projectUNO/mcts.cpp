#include "mcts.h"


using namespace std;

MCTS* createMCTS(list** h, stack** cp)
{
	MCTS* m = new MCTS;

	m->visited = 0;
	m->value = 0;
	m->xvalue = 0;
	m->yvalue = 0;
	m->simulated = 0;

	m->parent = NULL;
	m->children = NULL;


	m->hand = listCopy(h);
	m->possiblePlays = NULL;


	m->cardsPlayed = stackCopy(cp);

	return m;
}

void destroyMCTS(MCTS* mcts)
{
	//dfs post order i usuwanie dzieci:
	MCTSchildrenList* tmp = (mcts)->children;
	while (tmp != NULL)
	{
		destroyMCTS(tmp->mcts);
		tmp = tmp->next;
	}

	if ((mcts->hand) != NULL)
	{
	destroyList(&mcts->hand);
	}
	if (mcts->cardsPlayed != NULL)
	{
		destroyStack(&mcts->cardsPlayed);
	}

	free(mcts);

}


MCTSchildrenList* createChildrenlist()
{
	MCTSchildrenList* m = NULL;
	return m;
}

void MCTSappendChild(MCTSchildrenList** head, MCTS* mcts)
{
	if (*head == NULL)
	{
		*head = (MCTSchildrenList*)malloc(sizeof(MCTSchildrenList));
		(*head)->mcts = mcts;
		(*head)->next = NULL;
	}
	else
	{
		MCTSchildrenList* newItem = (MCTSchildrenList*)malloc(sizeof(MCTSchildrenList));
		newItem->mcts = mcts;
		newItem->next = *head;
		(*head) = newItem;
	}
}



card* findBestCard(MCTS* mcts, int depth, int simDepth)
{

	//printf("AI - rozpoczynam proces findBestCard\n");

	for (int i = 0; i < depth; i++)
	{
		//printf("AI - findBestCard:: depth: %d\n", i);

		//traverse
		MCTS* nextState = NULL;

		//printf("AI - rozpoczynam Traverse\n");

		nextState = traverse(mcts);

		//printf("AI - koniec traverse \n");

		//expand || simulate and backpropagate
		if (nextState->simulated || i == 0)
		{
			//printf("AI - rozpoczynam expand \n");
			MCTSexpand(nextState);
			//printf("AI - koniec expand \n");

		}
		else
		{
			//printf("AI - rozpoczynam simulate \n");
			MCTSsimulateState(nextState, simDepth);
			//printf("AI - koniec backpropagate \n");
		}
	}


	//wybierz najczesciej odwiedzany child glownego wierzcholka po symulacjach
	float maximum = 0;
	MCTS* best = createMCTS(&mcts->hand, &mcts->cardsPlayed);
	MCTSchildrenList* tmp = mcts->children;
	while (tmp != NULL)
	{
		if (tmp->mcts->visited > maximum)
		{
			best = tmp->mcts;
			maximum = tmp->mcts->visited;
		}

		tmp = tmp->next;
	}

	card* bestCardToPlay = best->cardsPlayed->c;

	//printf("AI - udalo mi sie wybrac karte:");
	//getCardFromId(bestCardToPlay->id);
	
	destroyMCTS(mcts);

	return bestCardToPlay;
}

MCTS* traverse(MCTS* mcts)
{
	mcts->visited = mcts->visited + 1;

	if (mcts->children == NULL)
	{
		//printf("AI - traverse:: znalazlam lisc\n");
		return mcts;
	}

	printf("");
	MCTS* bestChild = MCTSfindBestChild(mcts);
	//printf("AI - traverse:: znalazlam najlepsze dziecko\n");

	printf("");
	traverse(bestChild);

}

void MCTSexpand(MCTS* mcts)
{
	//sprawdz dostepne karty
	printf("");
	mcts->possiblePlays = MCTSfindPossiblePlays(mcts->cardsPlayed, mcts->hand);
	printf("");

	list* startingHand = mcts->hand;
	stack* startingCp = mcts->cardsPlayed;

	list* tmp = mcts->possiblePlays;
	while (tmp != NULL)
	{
		printf("");
		//getCardFromId(tmp->c->id);

		//pokaz startingHand
		//printf("AI - expand:: reka startowa:\n");
		//list* ltmp = startingHand;
		//while (ltmp != NULL)
		//{
		//	getCardFromId(ltmp->c->id);
		//	ltmp = ltmp->next;
		//}

		//stworz nowy childrenNode
		//zdejmij karte do zagrania z hand do cp
		//printf("AI -expand:: tworze pusta liste pomocnicza - cardPosition \n");
		list* cardPosition = createList();
		//printf("AI - expand:: lista pomocnicza stworzona \n");

		//printf("AI - expand:: szukam karty w rece z listy possiblePlays \n");
		cardPosition = MCTSfindCardbyId(mcts, tmp->c->id);
		//printf("AI - expand:: znalazlam karte z  listy possiblePlays na rece \nKarta to: ");
		//getCardFromId(cardPosition->c->id);

		MCTS* newState = createMCTS(&startingHand, &startingCp);


		newState->parent = mcts;

		push(&newState->cardsPlayed, cardPosition->c);
		deleteFromListById(&newState->hand, cardPosition->c->id);


		//reka w newState
		//printf("AI - expand:: reka w newState:\n");
		//ltmp = newState->hand;
		//while (ltmp != NULL)
		//{
		//	getCardFromId(ltmp->c->id);
		//	ltmp = ltmp->next;
		//}

		//cp w newState
		//printf("AI - expand:: cp w newState:\n");
		//stack* stmp = newState->cardsPlayed;
		//while (stmp != NULL)
		//{
		//	getCardFromId(stmp->c->id);
		//	stmp = stmp->next;
		//}


		//dodaj go do listy mcts->children
		MCTSappendChild(&mcts->children, newState);
		printf("");


		tmp = tmp->next;
	}
}

list* MCTSfindPossiblePlays(stack* cp, list* hand)
{
	//przejzyj karty w rece i dodaj mozliwe do zagrania do listy possiblePlays

	//printf("findPossiblePlays:: \n");

	//printf("TOP CARD: ");
	//getCardFromId(cp->c->id);

	list* tmp = hand;
	list* possiblePlays = createList();
	while (tmp != NULL)
	{
		if (checkCardCorrect(tmp->c, (cp)))
		{

			if (!isBlackCard(tmp->c))
			{
				listAppend(&possiblePlays, tmp->c);
			}

		}
		tmp = tmp->next;
	}


	//POKAZ POSSIBLE PLAYS:
	//printf("findPossiblePlays:: mozliwe ruchy:\n");
	//list* possibleTmp = possiblePlays;
	//while (possibleTmp != NULL)
	//{
	//	getCardFromId(possibleTmp->c->id);
	//	possibleTmp = possibleTmp->next;
	//}

	return possiblePlays;

}

list* MCTSfindCardbyId(MCTS* mcts, int id)
{
	//printf("AI - findCardById:: rozpoczynam szukanie karty na rece id: %d \n",id);
	list* tmp = mcts->hand;

	while (tmp != NULL)
	{
		//znaleziono karte o szukanym id
		if (tmp->c->id == id)
		{
			//printf("AI - findCardById:: znalezniono karte o id: %d \n",id);
			return tmp;
		}

		tmp = tmp->next;
	}

	//printf("AI - findCardById:: nie znaleziono karty o id: %d\n",id);

	return NULL;
}

MCTS* MCTSfindBestChild(MCTS* mcts)
{
	MCTSchildrenList* tmp = mcts->children;

	float maximum = 0;
	MCTS* best = tmp->mcts;

	while (tmp != NULL)
	{
		//sprawdz wartosc dziecka i  wybierz najwieksza
		if (tmp->mcts->value > maximum)
		{
			maximum = tmp->mcts->value;
			best = tmp->mcts;
		}
		tmp = tmp->next;
	}

	return best;
}

void MCTSsimulateState(MCTS* mcts, int depth)
{
	int sumOfCardsleft = 0;
	int counter = 0;
	mcts->simulated = 1;

	//printf("AI - simulateState:: rozpoczynam proces symulacji \n");

	while (counter < depth)
	{
		//printf("AI - simulateState:: simDepth: %d \n", counter);

		//tworzy liste kart w talii+na rece przeciwnika

		//printf("AI - simulateState:: tworze liste cardsLeft\n");
		list* cardsLeft = MCTScreateSimulationListOfCardsLeft(mcts);

		listShuffle(&cardsLeft);

		//printf("AI - simulateState:: stworzylam liste cardsLeft\n");


		//pomocnicze listy/ stosy
		list* hand = listCopy(&mcts->hand);

		//pokaz reke:
		//printf("AI - simulateState:: moja aktualna reka:\n");
		list* tmpHand = hand;
		while (tmpHand != NULL)
		{
			//getCardFromId(tmpHand->c->id);
			tmpHand = tmpHand->next;
		}

		stack* cp = stackCopy(&mcts->cardsPlayed);
		//pokaz stos cp
		//printf("AI - simulateState:: moje aktualne cardsPlayed:\n");
		stack* tmpCp = cp;
		while (tmpCp != NULL)
		{
			//getCardFromId(tmpCp->c->id);
			tmpCp = tmpCp->next;
		}


		list* possiblePlays = MCTSfindPossiblePlays(cp, hand);

		//printf("AI - simulateState:: SYMULACJA\n");

		while (listSize(possiblePlays) > 0)
		{

			//printf("AI - simulateState:: ruch przeciwnika (czlowiek) - losowanie \n");
			//przeciwnik zagrywa karte
			list* tmp = cardsLeft;

			//printf("AI - simulateState:: ostatnio zagrana karta:");
			//getCardFromId(cp->c->id);

			while (tmp != NULL)
			{

				//printf("AI - simulateState:: przeciwnik probuje zagrac karte ");
				//getCardFromId(tmp->c->id);

				if (checkCardCorrect(tmp->c, cp))
				{
					card c = *tmp->c;

					//printf("AI - simulateState:: przeciwnik zagrywa: ");
					//getCardFromId(c.id);

					deleteFromList(&cardsLeft, &c);
					push(&cp, &c);
					break;
				}

				tmp = tmp->next;
			}


			//wybieram karte do zagrania, jesli nie mam nic do zagrania - dodaj liczbe kart na rece do wyniku i powtorz symulacje. wpp zagraj wybrana karte
			//printf("AI - simulateState:: Tworze nowe possiblePlays\n");
			possiblePlays = MCTSfindPossiblePlays(cp, hand);
			//printf("AI - simulateState:: stworzylam nowe possiblePlays\n");

			//nie mam nic do zagrania
			if (listSize(possiblePlays) == 0)
			{
				//printf("AI - simulateState:: nie mam nic do zagrania - koniec KROKu %d \n", counter);
				sumOfCardsleft += listSize(hand);
				//counter++;
				continue;
			}
			else //zagrywam karte, usuwam ja z reki i dodaje na cp
			{
				//printf("AI - simulateState:: mam karte do zagrania\n");
				int randomCardPosition = randomInt(0, listSize(possiblePlays) - 1);
				//printf("AI - simulateState:: RANDOM CARD POSITION: %d\n", randomCardPosition);


				list* ltmp = possiblePlays;
				for (int i = 0; i < randomCardPosition; i++)
				{
					ltmp = ltmp->next;
				}

				card c = *ltmp->c;
				//printf("AI - simulateState:: zagrywam karte: \n");
				//getCardFromId(c.id);

				deleteFromList(&hand, &c);
				push(&cp, &c);
			}
		}

		//nie mam nic do zagrania
		if (listSize(possiblePlays) == 0)
		{
			//printf("AI - simulateState:: nie mam nic do zagrania - koniec KROKu %d \n", counter);
			sumOfCardsleft += listSize(hand);
			counter++;

			destroyStack(&cp);
			destroyList(&hand);
			destroyList(&possiblePlays);
			destroyList(&cardsLeft);
			
			
			continue;
		}

	}

	//printf("AI - simulateState:: KONIEC SYMULACJI\n");

	int avgSum = ceil(sumOfCardsleft / depth);

	float value = 1 / avgSum;

	mcts->xvalue = avgSum;

	//printf("AI - simulateState:: srednia kart na rece po symulacji: %d\n", avgSum);

	//printf("AI - simulateState:: ROZPOCZYNAM BACKPROPAGATE \n");
	MCTSbackpropagate(mcts);

}

list* MCTScreateSimulationListOfCardsLeft(MCTS* mcts)
{
	//printf("AI -  createSimulationListOfCardsleft:: \n");
	//poczatkowy deck:
	//printf("AI -  createSimulationListOfCardsleft:: tworze pusta liste cardsLeft\n");
	list* cardsLeft = createList();
	//printf("AI -  createSimulationListOfCardsleft:: pusta lista utworzona\n");

	//printf("AI -  createSimulationListOfCardsleft:: podprocedura wypelniania kartami startowymi\n");
	cardsLeft = createListOfNormalCards();
	//printf("AI -  createSimulationListOfCardsleft:: koniec podprocedury wypelniania kartami startowymi\n");


	//zdejmij z listy karty, ktore sa na rece lub zagrane
	//reka
	list* ltmp = mcts->hand;
	while (ltmp != NULL)
	{

		//printf("AI -createSimulationListOfCardsleft:: usuwam karte znajdujaca sie na mojej rece: ");
		//getCardFromId(ltmp->c->id);
		deleteFromList(&cardsLeft, ltmp->c);
		ltmp = ltmp->next;
	}

	//cp
	stack* stmp = mcts->cardsPlayed;
	while (stmp != NULL)
	{
		//printf("AI -createSimulationListOfCardsleft:: usuwam karte znajdujaca sie na cp: ");
		//getCardFromId(stmp->c->id);
		deleteFromList(&cardsLeft, stmp->c);
		stmp = stmp->next;
	}

	/*printf("AI -  createSimulationListOfCardsleft:: talia cardsLeft:\n");
	list* tmp = cardsLeft;
	while (tmp != NULL)
	{
		getCardFromId(tmp->c->id);
		tmp = tmp->next;
	}
	printf("AI -  createSimulationListOfCardsleft:: koniec talii cardsLeft \n");*/


	return cardsLeft;

}

list* createListOfNormalCards()
{
	list* deck = createList();

	//dodaj karty z wartoœci¹ 0 - po jednej na kolor
	for (int color = red; color <= yellow; color++)
	{
		listAppend(&deck, generateCard(0, color));
	}


	//dodaj karty z wartoœci¹ 1-9 - po dwie na kolor:
	for (int color = red; color <= yellow; color++)
	{
		for (int value = 1; value <= 9; value++)
		{
			listAppend(&deck, generateCard(value, color));
			listAppend(&deck, generateCard(value, color));
		}
	}

	//dodaj karty stop, zmiana kierunku, weŸ 2 - po dwie na kolor
	for (int color = red; color <= yellow; color++)
	{
		for (int value = stop; value <= draw2; value++)
		{
			listAppend(&deck, generateCard(value, color));
			listAppend(&deck, generateCard(value, color));
		}
	}

	return deck;
}

float MCTSevaluate(MCTS* mcts)
{
	float x = mcts->xvalue;

	float c = sqrt(2);

	float parent = 0;

	if (mcts->parent == NULL)
	{
		parent = mcts->visited;
	}
	else
	{
		parent = log(mcts->parent->visited);
	}


	float visited = mcts->visited;

	float root = sqrt(parent / visited) * c;


	return x + root;

}

void MCTSbackpropagate(MCTS* mcts) {
	MCTS* tmp = mcts;


	//printf("AI - backpropagate:: start\n");

	while (tmp != NULL)
	{
		//printf("AI - backpropagate:: rozpoczynam przypisywanie value\n");
		tmp->value = MCTSevaluate(tmp);
		//printf("AI - backpropagate:: value zostalo przypisane: value = %f\n",tmp->value);

		//printf("AI - backpropagate:: szukam rodzica\n");
		tmp = tmp->parent;
		//printf("AI - backpropagate:: rodzic znaleziony\n");
	}
	//printf("AI - backpropagate:: zakonczono update drzewa\n");

}

int findPositionOfCard(list* hand, card* c)
{
	int pos = 0;
	list* tmp = hand;

	while (tmp->c->id != c->id && tmp != NULL)
	{
		pos++;
		tmp = tmp->next;
	}

	if (tmp == NULL)
	{
		return NULL;
	}

	return pos;
}

list* findSpecialCards(list* hand)
{
	//przejzyj karty w rece i dodaj karty specjalne do specials

	list* specials = createList();
	list* tmp = hand;

	while (tmp != NULL)
	{
		if (isBlackCard(tmp->c))
		{
			listAppend(&specials, tmp->c);
		}

		tmp = tmp->next;
	}

	return specials;
}

card* AIEnemyHasUno(game* g)
{
	//sprobuj zagrac +2, +4
	card* blackCard = NULL;
	list* tmpHand = g->players[g->turn]->hand;
	int valueMask = 15;
	int id = 0;
	int value = 0;
	while (tmpHand != NULL)
	{
		id = tmpHand->c->id;
		value = id & valueMask;

		if (value == 12)
		{
			if (checkCardCorrect(tmpHand->c, g->cardsPlayed))
			{
				blackCard = tmpHand->c;
				playCard(g, findPositionOfCard(g->players[g->turn]->hand, blackCard) + 1);
				break;
			}

		}

		if (value == 14)
		{
			blackCard = tmpHand->c;
			AiPlayBlackCard(g, findPositionOfCard(g->players[g->turn]->hand, blackCard) + 1);
			break;
		}

		tmpHand = tmpHand->next;
	}
	return blackCard;
}