#pragma once
#include "cards.h"
#include "utils.h"

//Linked list structure
struct list {
	card* c;
	list* next;
};

//Stores information about player
struct player {
	int id;
	list* hand;
	int uno;
	bool comp;
	bool compDidAnAction;
	bool playerDidAnAction;

	sf::String* name;
};


//Creates a new player with id, comp flag to determine if new player is a computer. Returns a pointer to the player.
player* createPlayer(int id,bool comp,std::string);


//deletes player frmo memory
void deletePlayer(player*);

//Player draws a card
card* drawCard(game* g,int playerId);



//Player plays a card from given position from hand 
void playCard(game* g, int position);

//Returns true if the card is matching top of the given stack of cards, else returns false. 
int checkCardCorrect(card* cardToPlay, stack* topCard);

//Creates an empty linked list of cards - used for players hands
list* createList();

//destroys a list
void destroyList(list** s);

//Returns size of a linked list
int listSize(list* l);

//Appends a card to the begining of the linked list
card* listAppend(list** head, card* c);

//Deletes given card from list
card* deleteFromList(list** head, card* c);

//Prints all elements of list
void showHand(game *g);

//Deletes item from list by given id
void deleteFromListById(list** head, int id);

//Returns copy of a list
list* listCopy(list** head);

//Randomly shuffles items in list
void listShuffle(list** head);

//Reverses the list
void reverseList(list** head);

//prints given list
void showList(list* head);

//sorts given list by cardId ascending
void sortList(list* head);

//returns true if list is empty
bool listEmpty(list* head);

//Current player says UNO - if player has only 1 card left
void uno(game* g);

//AI plays black card and calculates best color 
void AiPlayBlackCard(game* g, int pos);
