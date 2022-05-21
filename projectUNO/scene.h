#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics.hpp>
#include "PlayButton.h"
#include "ExitButton.h"
#include "IncrementButton.h"
#include "CheckboxButton.h"
#include "gameManager.h"

#include "HandDisplay.h"
#include "TopCard.h"
#include "DrawCardButton.h"
#include "ChooseColorButton.h"
#include "YesNoButton.h"
#include "CloseButton.h"


	struct mainMenuResources {

		PlayButton* playButton;
		ExitButton* exitButton;

		sf::Sprite* logo;
		sf::RectangleShape* background;
		

	};
	struct setupMenuResources {
		
		sf::RectangleShape* background;

		sf::Sprite* players_label;
		
		IncrementButton* box_plus;
		IncrementButton* box_minus;

		sf::Sprite* player1_label;
		sf::Sprite* player1_name_label;

		sf::Sprite* player2_label;
		sf::Sprite* player2_name_label;
		CheckboxButton* player2_checkbox;

		sf::Sprite* player3_label;
		sf::Sprite* player3_name_label;
		CheckboxButton* player3_checkbox;

		sf::Sprite* player4_label;
		sf::Sprite* player4_name_label;
		CheckboxButton* player4_checkbox;

		PlayButton* startGameButton;

	};
	struct gameResources {

		//EndGame
		bool showEndGame;
		sf::RectangleShape* endGameBg;
		sf::Text* winnerText;
		PlayButton* button;


		sf::RectangleShape* handBg;
		sf::RectangleShape* rightSideBg;
		sf::RectangleShape* changeColorBg;
		sf::RectangleShape* horizontalLine;
		sf::RectangleShape* verticalLine;


		TopCard* topCard;
		sf::Sprite* directionIndicator;

		DrawCardButton* drawCardButton;

		//wczytgac tekstury, zainicjoowac w mainie, wyswietlic w scene.cpp
		bool showChangeColorUI;
		sf::Sprite* changeColorLabel;
		ChooseColorButton* colorRedButton;
		ChooseColorButton* colorBlueButton;
		ChooseColorButton* colorGreenButton;
		ChooseColorButton* colorYellowButton;


		bool showPlayDrawnCardMenu;
		bool showOnlyCardDrawn;

		bool draw0indicator;
		bool draw1indicator;
		bool draw2indicator;
		bool draw3indicator;

		sf::RectangleShape* PlayDrawnMenuBg;
		sf::Sprite* drawnCard;
		sf::Sprite* drawnCardLabel;
		YesNoButton* yesButton;
		YesNoButton* noButton;


		//player data
		sf::RectangleShape* player0bg;
		sf::Text* player0name;
		sf::Text* player0cards;
		sf::Text* player0uno;
		sf::Sprite* turnIndicator0;

		sf::RectangleShape* player1bg;
		sf::Text* player1name;
		sf::Text* player1cards;
		sf::Text* player1uno;
		sf::Sprite* turnIndicator1;

		sf::RectangleShape* player2bg;
		sf::Text* player2name;
		sf::Text* player2cards;
		sf::Text* player2uno;
		sf::Sprite* turnIndicator2;

		sf::RectangleShape* player3bg;
		sf::Text* player3name;
		sf::Text* player3cards;
		sf::Text* player3uno;
		sf::Sprite* turnIndicator3;


		//zaslona
		bool showVeil;
		bool showVeilButton;

		sf::RectangleShape* veil;
		sf::RectangleShape* veilBg;
		CloseButton* veilClose;
		sf::Text* veilLabel;
		sf::RectangleShape* veilBorder0;
		sf::RectangleShape* veilBorder1;
		sf::RectangleShape* veilBorder2;
		sf::RectangleShape* veilBorder3;


	};
	struct sceneManager {

		int currentScene;

		mainMenuResources* mainMenu;
		setupMenuResources* setupMenu;
		gameResources* gameUI;
	};


	void createPlayerDataUI(gameManager* gm);
	sceneManager* createSceneManager();
	mainMenuResources* createMainMenu();
	setupMenuResources* createSetupMenu();
	gameResources* createGameUI();

	void drawGame(gameManager*, sf::RenderWindow&);
	void drawSetupMenu(gameManager*, sf::RenderWindow&);
	void drawMainMenu(gameManager*, sf::RenderWindow&);
	void drawHandDisplay(gameManager* gm, HandDisplay* handDisplay, sf::RenderWindow& window);

	void changeScene(gameManager*, int, HandDisplay*);
	void setupScene(gameManager*, HandDisplay* handDisplay);
	void drawGameUiBg(gameManager* gm, HandDisplay* handDisplay, sf::RenderWindow& window);
	void resetSceneBeforeNewGame(gameManager* gm, HandDisplay* handDisplay);




#endif // !SCENE_H