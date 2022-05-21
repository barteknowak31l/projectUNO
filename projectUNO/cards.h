#ifndef CARDS_H
#define CARDS_H
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <string>
#include "gameManager.h"


using namespace std;

	//Structure that stores data about a card
	struct card{
		int id;
		sf::Texture* texture;
	};

	//Stack of cards that stores struct card items
	struct stack {
		card* c;
		stack* next;
	};

	//Push a card to the given stack
	unsigned int push(stack**, card*);
	
	//Pop a card from the given stack, returns popped card 
	card* pop(stack**);

	//Boolean to determine if stack is empty
	int empty(stack*);

	//Returns size of the given stack
	int size(stack*);

	//Prints all elements on the given stack
	void show(stack*);

	//Reverses the order of items on the given stack
	void reverseStack(stack** s);

	//Creates an empty stack, returns a pointer to new stack
	stack* createStack();

	//Destroys a stack
	void destroyStack(stack** s);

	//Returns copy of a given stack
	stack* stackCopy(stack** head);

	//Stores values of colors of the cards
	enum color {
		red = 0,
		blue = 1,
		green = 2,
		yellow = 3
	};
	
	//Stores values of special cards
	enum value {
		stop = 10,
		changeDir = 11,
		draw2 = 12,
		changeCol = 13,
		changeColDraw4 = 14

	};

	//Initializes an unique instance of a card,(to determine value parameter use enum value (or value 0-9), to determine color use enum color) returns an instance of a card
	card* generateCard(int value, int color);


	//permamently destroys an instance of card - usefull during reset
	void destroyCard(card* c);
	
	//Generates all cards and puts them into game deck, returns new starting deck
	stack* generateStartingDeck();
	
	//Given the id of card returns a mnemonic i.e 010111 -> blue 7 
	void getCardFromId(int id);
	
	//Executes at the begining of a game, shuffles game deck
	void shuffle(stack** deck);

	//Takes every card (apart of first one) from cardsPlayed pile, shuffles them and puts them into game deck
	void reshuffle(game* g);
	
	//Executes at the begining of a game, puts first non-special card from deck to a cardsPlayed pile 
	void putCardOnTop(game* g);

	//Checks if the given card is special and determines its behaviour: returns 0 - card not special/ 1- stop, changeDir, draw2/ 2 - changeCol, changeCol +4
	int isCardSpecial(game *g, card* c);

	//Check if a card is changeColor or changeColor +4
	int isBlackCard(card* c);

	//Event after any player plays Stop card
	void specialStop(game* g);

	//Event after any player plays ChangeDirection card
	void specialChangeDir(game* g);

	//Event after any player plays Draw2 card
	void specialDraw2(game* g);

	//Event after any player plays changeColor card
	void specialChangeColor(game* g, card* c);

	//Event after any player plays changeColor +4 card
	void specialChangeColorDraw4(game* g, card* c);

	//AI plays changeCol with given color - evaluated by player::AIPlaysBlackCard
	void AiSpecialChangeColor(game* g, card* c, int color);

	//AI plays changeColDraw4 - evaluated by player::AIPlaysBlackCard
	void AiSpecialChangeColorDraw4(game* g, card* c, int color);


	//returns value id of given cardId
	int getCardValueID(int id);

	//returns colorId of given cardId
	int getCardColorID(int id);

#endif