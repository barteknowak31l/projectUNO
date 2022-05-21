#pragma once
#include "cards.h"
#include "gameManager.h"
#include "player.h"
#include "utils.h"

struct card;
struct list;
struct MCTSchildrenList;

//Node of MCTS tree
struct MCTS {

	float value;
	float xvalue;
	float yvalue;
	float visited;
	bool simulated;

	MCTS* parent;
	MCTSchildrenList* children;
	list* hand;
	list* possiblePlays;
	stack* cardsPlayed;

};

//List of MCTS node's children
struct MCTSchildrenList {
	MCTS* mcts;
	MCTSchildrenList* next;
};

//Creates MCTS node
MCTS* createMCTS(list** h, stack** cp);

//Destroys MCTS tree
void destroyMCTS(MCTS* mcts);

//Creates Empty MCTSChildrenList
MCTSchildrenList* createChildrenlist();

//Appends MCTS node to MCTSChildrenList
void MCTSappendChild(MCTSchildrenList** head, MCTS* mcts);

//AI main function - returns best card to play 
card* findBestCard(MCTS* mcts, int depth, int simDepth);

//MCTS TRAVERSE STEP - Traverses MCTS tree and finds best child - best - highest value calculated by MCTSEvaluate
MCTS* traverse(MCTS* mcts);

//MCTS EXPAND STEP - Expands MCTS tree by new possible plays
void MCTSexpand(MCTS* mcts);

//Returns list of cards which are possible to play at the moment
list* MCTSfindPossiblePlays(stack* cp, list* hand);

//Finds card with given id on a given list, returns pointer to that list element, returns NULL if a card is not found
list* MCTSfindCardbyId(MCTS* mcts, int id);

//Searches the MCTSChildrenList and returns MCTS with highest value found
MCTS* MCTSfindBestChild(MCTS* mcts);

//MCTS SIMULATION STEP - Performs a simulation of a game on a leaf node - at the end node is evaluated by avg number of cards left in all simulations, depth - number of simulations, SIMULATION SKIPS BLACK CARDS
void MCTSsimulateState(MCTS* mcts, int depth);

//MCTS simulation utility function - creates a list of cards left in deck and other players hands in particular simulation state.
list* MCTScreateSimulationListOfCardsLeft(MCTS* mcts);

//MCTS simulation utility function - creates basic deck of cards without black cards - it it processed by MCTScreateSimulationListOfCardsLeft function
list* createListOfNormalCards();

//Evaluates a node by number of visits, number of its parents visits and its xValue <-> 1/(average sum of cards left after simulations)
float MCTSevaluate(MCTS* mcts);

//MCTS BACKPROPAGATION STEP - updates simulated node and its ancestors value
void MCTSbackpropagate(MCTS* mcts);

//Returns position of a card on a given list, returns NULL if card is not found
int findPositionOfCard(list* hand, card* c);

//Retuns a list of special cards that are on given list of cards - chooses special cards from given list, appends them to new list and returns that list
list* findSpecialCards(list* hand);

//Checks if next player has UNO - if so, AI tries to disturb that player by playing +2 or +4. If AI does not have those cards, it proceeds to regular card selection procees
card* AIEnemyHasUno(game* g);