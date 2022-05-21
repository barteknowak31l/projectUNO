#pragma once
#ifndef GAMAMANAGER_H
#define GAMAMANAGER_H

#include <SFML/Graphics.hpp>
#include <string>

#include "TextButton.h"

struct sceneManager;
struct player;
struct stack;
class TextButton;

struct CardTextures {

	sf::Texture* emptyCard;

	sf::Texture* red0;
	sf::Texture* red1;
	sf::Texture* red2;
	sf::Texture* red3;
	sf::Texture* red4;
	sf::Texture* red5;
	sf::Texture* red6;
	sf::Texture* red7;
	sf::Texture* red8;
	sf::Texture* red9;
	sf::Texture* redPlus2;
	sf::Texture* redReverse;
	sf::Texture* redStop;

	sf::Texture* blue0;
	sf::Texture* blue1;
	sf::Texture* blue2;
	sf::Texture* blue3;
	sf::Texture* blue4;
	sf::Texture* blue5;
	sf::Texture* blue6;
	sf::Texture* blue7;
	sf::Texture* blue8;
	sf::Texture* blue9;
	sf::Texture* bluePlus2;
	sf::Texture* blueReverse;
	sf::Texture* blueStop;

	sf::Texture* green0;
	sf::Texture* green1;
	sf::Texture* green2;
	sf::Texture* green3;
	sf::Texture* green4;
	sf::Texture* green5;
	sf::Texture* green6;
	sf::Texture* green7;
	sf::Texture* green8;
	sf::Texture* green9;
	sf::Texture* greenPlus2;
	sf::Texture* greenReverse;
	sf::Texture* greenStop;

	sf::Texture* yellow0;
	sf::Texture* yellow1;
	sf::Texture* yellow2;
	sf::Texture* yellow3;
	sf::Texture* yellow4;
	sf::Texture* yellow5;
	sf::Texture* yellow6;
	sf::Texture* yellow7;
	sf::Texture* yellow8;
	sf::Texture* yellow9;
	sf::Texture* yellowPlus2;
	sf::Texture* yellowReverse;
	sf::Texture* yellowStop;


	sf::Texture* blackColor;
	sf::Texture* blackColorRed;
	sf::Texture* blackColorBlue;
	sf::Texture* blackColorGreen;
	sf::Texture* blackColorYellow;


	sf::Texture* blackColorPlus4;
	sf::Texture* blackColorPlus4red;
	sf::Texture* blackColorPlus4blue;
	sf::Texture* blackColorPlus4green;
	sf::Texture* blackColorPlus4yellow;



};
struct Textures {
	sf::Texture* checkbox_yes;
	sf::Texture* checkbox_no;
	CardTextures* cardTextures;

	sf::Texture* changeColorLabelTexture;
	sf::Texture* colorRedButtonTexture;
	sf::Texture* colorBlueButtonTexture;
	sf::Texture* colorGreenButtonTexture;
	sf::Texture* colorYellowButtonTexture;

	
	//playInstantLabel
	sf::Texture* playInstantLabel;
	
	//ButtonTextures
	sf::Texture* drawCardButtonTexture;
	
	sf::Texture* turnIndicator;

	sf::Texture* directionIndicator;
	sf::Texture* directionIndicatorReversed;

	sf::Texture* logo;
	sf::Texture* box_ai;
	sf::Texture* box_human;

	sf::Texture* box_plus;
	sf::Texture* box_minus;
	sf::Texture* emptyLabel;
	sf::Texture* player1Label;
	sf::Texture* player2Label;
	sf::Texture* player3Label;
	sf::Texture* player4Label;
	sf::Texture* playersLabel;

	sf::Texture* btn_play;
	sf::Texture* btn_exit;

	sf::Image* icon;

	sf::Cursor* cursor;
	sf::Image* cur;
	sf::Image* cur_cl;

};

//GameManager stores all important data and references
struct gameManager;

//Stores game instance information
struct game {

	int currentScene;

	player** players;
	stack* deck;
	stack* cardsPlayed;

	int playerCount;
	int startingHandSize;

	int turn;
	int playDirection; // 1 wedlug wskazowek zegara. -1 przeciwnie

	bool skipTurn;
	bool gameStarted;
	
	gameManager* gm;

	int newColorOfCard;
	int newColorOfCardPosition;

	bool playerClickedYesNo;

};


struct gameManager {
	game* game;
	sceneManager* sceneManager;
	Textures* textures;


	sf::Font* font;

	bool exitGame;

	int playerCount;
	int playerType[4]; //0 - hhuman 1 -comp


	int mctsDepth;
	int mctsSimDepth;

	bool startTurn;

	float waitTime;
	float currentWaitTime;



	TextButton* player0text;
	TextButton* player1text;
	TextButton* player2text;
	TextButton* player3text;




};

//creates GamaManager instance and loads textures
gameManager* createGameManager();

void loadTextures(gameManager* gm);

//Sets mcts data
void setupMCTS(gameManager* gm, int d, int sd);

//creates a game logic instance
game* createGame(gameManager*gm, int startingHandSize);

//sets all card textures to proper cards
void setCardTextures(gameManager* gm, stack* cards);

//clears memory after finished game
game* deleteGame(game* g);

//creates player array
void createPlayers(gameManager*, game*);

//executes at the begining of the game, deals cards to all players
void dealTheCards(game* g);

//exexutes just before next turn - changes the turn
void nextTurn(game* g);

//Changes the turn counter to the previous turn - used in draw2 / draw4 cards
int nextPlayerId(game* g);

//Changes current scene: 0 - main menu, 1 - game setup, 2 - game
void changeScene(game* g, int scene);

#endif // GAMAMANAGER_H