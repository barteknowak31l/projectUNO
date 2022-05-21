#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "scene.h"
#include "HandDisplay.h"
#include "CardButton.h"
#include "TextButton.h"


struct sceneManager scene;

sceneManager* createSceneManager()
{
	sceneManager* s = (sceneManager*)malloc(sizeof(sceneManager));
	s->currentScene = 0;
	s->mainMenu = createMainMenu();
	s->setupMenu = createSetupMenu();
	s->gameUI = createGameUI();
	return s;
}

void changeScene(gameManager* gm,int s,HandDisplay* handDisplay)
{
	gm->sceneManager->currentScene = s;
	setupScene(gm,handDisplay);
}
void setupScene(gameManager* gm, HandDisplay* handDisplay)
{
	Button::update();

	switch (gm->sceneManager->currentScene)
	{
	case 0: // main menu
	{
		if (gm->game != NULL)
		{
			resetSceneBeforeNewGame(gm, handDisplay);
		}

		//wylacz gameUI
		gm->sceneManager->gameUI->button->setActive(false);
		
		gm->sceneManager->gameUI->colorRedButton->setActive(false);
		gm->sceneManager->gameUI->colorBlueButton->setActive(false); 
		gm->sceneManager->gameUI->colorGreenButton->setActive(false); 
		gm->sceneManager->gameUI->colorYellowButton->setActive(false); 
		gm->sceneManager->gameUI->drawCardButton->setActive(false); 
		gm->sceneManager->gameUI->noButton->setActive(false); 
		gm->sceneManager->gameUI->yesButton->setActive(false); 
		gm->sceneManager->gameUI->veilClose->setActive(false); 

		//wylacz setupMenu
		gm->sceneManager->setupMenu->startGameButton->setActive(false);
		gm->sceneManager->setupMenu->box_minus->setActive(false); 
		gm->sceneManager->setupMenu->box_plus->setActive(false);
		gm->sceneManager->setupMenu->player2_checkbox->setActive(false); 
		gm->sceneManager->setupMenu->player3_checkbox->setActive(false); 
		gm->sceneManager->setupMenu->player4_checkbox->setActive(false); 
		gm->sceneManager->setupMenu->startGameButton->setActive(false); 

		gm->player0text->setActive(false);
		gm->player1text->setActive(false);
		gm->player2text->setActive(false);
		gm->player3text->setActive(false);


		//wlacz mainMenu
		gm->sceneManager->mainMenu->playButton->setActive(true);
		gm->sceneManager->mainMenu->exitButton->setActive(true);




		break;
	}
	case 1: //setupMenu
	{
		//wylacz mainMenu
		gm->sceneManager->mainMenu->playButton->setActive(false);
		gm->sceneManager->mainMenu->exitButton->setActive(false);

		//wylacz gameUI
		gm->sceneManager->gameUI->button->setActive(false);
		
		gm->sceneManager->gameUI->colorRedButton->setActive(false);
		gm->sceneManager->gameUI->colorBlueButton->setActive(false);
		gm->sceneManager->gameUI->colorGreenButton->setActive(false);
		gm->sceneManager->gameUI->colorYellowButton->setActive(false);
		gm->sceneManager->gameUI->drawCardButton->setActive(false);
		gm->sceneManager->gameUI->noButton->setActive(false);
		gm->sceneManager->gameUI->yesButton->setActive(false);
		gm->sceneManager->gameUI->veilClose->setActive(false);

		//wlacz setupMenu
		gm->sceneManager->setupMenu->startGameButton->setActive(true);
		gm->sceneManager->setupMenu->box_minus->setActive(true);
		gm->sceneManager->setupMenu->box_plus->setActive(true);



		gm->player0text->setActive(true);
		gm->player0text->textBox.setString("");
		gm->player0text->text.str("");
		
		
		gm->player1text->setActive(true);
		gm->player1text->textBox.setString("");
		gm->player1text->text.str("");
		
		gm->player2text->setActive(true);
		gm->player2text->textBox.setString("");
		gm->player2text->text.str("");

		gm->player3text->setActive(true);
		gm->player3text->textBox.setString("");
		gm->player3text->text.str("");

		switch (gm->playerCount)
		{
		case 2:
		{
			gm->sceneManager->setupMenu->player2_checkbox->setActive(true);
			gm->sceneManager->setupMenu->player3_checkbox->setActive(false);
			gm->sceneManager->setupMenu->player4_checkbox->setActive(false);
			break;
		}

		case 3:
		{
			gm->sceneManager->setupMenu->player2_checkbox->setActive(true);
			gm->sceneManager->setupMenu->player3_checkbox->setActive(true);
			gm->sceneManager->setupMenu->player4_checkbox->setActive(false);
			break;
		}
		case 4:
		{
			gm->sceneManager->setupMenu->player2_checkbox->setActive(true);
			gm->sceneManager->setupMenu->player3_checkbox->setActive(true);
			gm->sceneManager->setupMenu->player4_checkbox->setActive(true);
			break;
		}

		}
		gm->sceneManager->setupMenu->startGameButton->setActive(true);




		break;
	}
	case 2: //gameUI
	{

		gm->game = createGame(gm, 7);
		createPlayerDataUI(gm);
		gm->sceneManager->gameUI->topCard->refreshTopCard(gm);
		handDisplay->refreshHandDisplay(gm);
		gm->startTurn = 1;

		//wylacz mainMenu
		gm->sceneManager->mainMenu->playButton->setActive(false);
		gm->sceneManager->mainMenu->exitButton->setActive(false);

		//wylacz setupMenu
		gm->sceneManager->setupMenu->startGameButton->setActive(false);
		gm->sceneManager->setupMenu->box_minus->setActive(false);
		gm->sceneManager->setupMenu->box_plus->setActive(false);
		gm->sceneManager->setupMenu->player2_checkbox->setActive(false);
		gm->sceneManager->setupMenu->player3_checkbox->setActive(false);
		gm->sceneManager->setupMenu->player4_checkbox->setActive(false);
		gm->sceneManager->setupMenu->startGameButton->setActive(false);

		gm->player0text->setActive(false);
		gm->player1text->setActive(false);
		gm->player2text->setActive(false);
		gm->player3text->setActive(false);


		

		//wlacz gameUI
		
		gm->sceneManager->gameUI->showEndGame = false;
		gm->sceneManager->gameUI->showChangeColorUI = false;
		gm->sceneManager->gameUI->showPlayDrawnCardMenu = false;
		//veil
		gm->sceneManager->gameUI->showVeil = true;
		gm->sceneManager->gameUI->showVeilButton = true;
		switch (gm->game->playerCount)
		{
		case 2:
		{
			if (gm->game->players[1]->comp)
			{
				gm->sceneManager->gameUI->showVeil = false;
				gm->sceneManager->gameUI->showVeilButton = false;
			}
			break;
		}

		case 3:
		{
			if (gm->game->players[1]->comp && gm->game->players[2]->comp)
			{
				gm->sceneManager->gameUI->showVeil = false;
				gm->sceneManager->gameUI->showVeilButton = false;
			}
			break;
		}
		case 4:
		{
			if (gm->game->players[1]->comp && gm->game->players[2]->comp && gm->game->players[3]->comp)
			{
				gm->sceneManager->gameUI->showVeil = false;
				gm->sceneManager->gameUI->showVeilButton = false;
			}
			break;
		}
		}


		gm->sceneManager->gameUI->button->setActive(false);
		gm->sceneManager->gameUI->colorRedButton->setActive(false);
		gm->sceneManager->gameUI->colorBlueButton->setActive(false);
		gm->sceneManager->gameUI->colorGreenButton->setActive(false);
		gm->sceneManager->gameUI->colorYellowButton->setActive(false);
		gm->sceneManager->gameUI->drawCardButton->setActive(true);
		gm->sceneManager->gameUI->noButton->setActive(false);
		gm->sceneManager->gameUI->yesButton->setActive(false);
		gm->sceneManager->gameUI->veilClose->setActive(true);

		break;
	}
	default:
	{
		break;
	}
	}

}
void resetSceneBeforeNewGame(gameManager* gm, HandDisplay* handDisplay)
{
	gm->game = deleteGame(gm->game);
	gm->sceneManager->gameUI->draw0indicator = true;
	gm->sceneManager->gameUI->draw1indicator = false;
	gm->sceneManager->gameUI->draw2indicator = false;
	gm->sceneManager->gameUI->draw3indicator = false;
	
	gm->playerType[0] = 0;
	gm->playerType[1] = 0;
	gm->playerType[2] = 0;
	gm->playerType[3] = 0;

	gm->sceneManager->setupMenu->player2_checkbox->setSprite(gm->textures->box_human);
	gm->sceneManager->setupMenu->player3_checkbox->setSprite(gm->textures->box_human);
	gm->sceneManager->setupMenu->player4_checkbox->setSprite(gm->textures->box_human);

	gm->playerCount = 2;


	gm->sceneManager->gameUI->showVeil = false;
	gm->sceneManager->gameUI->showVeilButton = false;
	gm->sceneManager->gameUI->showChangeColorUI = false;
	gm->sceneManager->gameUI->showOnlyCardDrawn = false;
	gm->sceneManager->gameUI->showPlayDrawnCardMenu = false;



}

mainMenuResources* createMainMenu() {

	mainMenuResources* m = (mainMenuResources*)malloc(sizeof(mainMenuResources));
	return m;
}
void drawMainMenu(gameManager* gm, sf::RenderWindow &window)
{
	//clear
	window.clear(sf::Color(6, 78, 52, 0.8));

	//draw ui
	window.draw(*(gm->sceneManager->mainMenu->background));
	window.draw(*(gm->sceneManager->mainMenu->playButton));
	window.draw(*(gm->sceneManager->mainMenu->exitButton));
	window.draw(*(gm->sceneManager->mainMenu->logo));
}


setupMenuResources* createSetupMenu()
{
	setupMenuResources* s = (setupMenuResources*)malloc(sizeof(setupMenuResources));
	return s;
}
void drawSetupMenu(gameManager* gm, sf::RenderWindow &window)
{
	//clear
	window.clear(sf::Color(6, 78, 52, 0.8));

	//draw ui
	window.draw(*(gm->sceneManager->setupMenu->background));
	window.draw(*(gm->sceneManager->setupMenu->players_label));

	window.draw(*(gm->sceneManager->setupMenu->box_plus));
	window.draw(*(gm->sceneManager->setupMenu->box_minus));
	
	window.draw(*(gm->sceneManager->setupMenu->player1_label));



	if (gm->player0text->isClicked)
	{
		gm->player0text->setHover();
	}

	window.draw(*gm->player0text);
	window.draw(gm->player0text->textBox);


	if ((*gm).playerCount > 1)
	{
		window.draw(*(gm->sceneManager->setupMenu->player2_label));

		if (gm->player1text->isClicked)
		{
			gm->player1text->setHover();
		}

		window.draw(*gm->player1text);
		window.draw(gm->player1text->textBox);
		window.draw(*(gm->sceneManager->setupMenu->player2_checkbox));

	}

	if (gm->playerCount > 2)
	{
		window.draw(*(gm->sceneManager->setupMenu->player3_label));

		if (gm->player2text->isClicked)
		{
			gm->player2text->setHover();
		}

		window.draw(*gm->player2text);
		window.draw(gm->player2text->textBox);
		window.draw(*(gm->sceneManager->setupMenu->player3_checkbox));
	}

	if (gm->playerCount > 3)
	{
		window.draw(*(gm->sceneManager->setupMenu->player4_label));

		if (gm->player3text->isClicked)
		{
			gm->player3text->setHover();
		}

		window.draw(*gm->player3text);
		window.draw(gm->player3text->textBox);
		window.draw(*(gm->sceneManager->setupMenu->player4_checkbox));
	}



	window.draw(*(gm->sceneManager->setupMenu->startGameButton));

}

gameResources* createGameUI()
{
	gameResources* g = (gameResources*)malloc(sizeof(gameResources));
	g->showChangeColorUI = false;
	g->showOnlyCardDrawn = false;

	g->player0bg = new sf::RectangleShape;
	g->player0name = new sf::Text;
	g->player0cards = new sf::Text;
	g->player0uno = new sf::Text;

	g->player1bg = new sf::RectangleShape;
	g->player1name = new sf::Text;
	g->player1cards = new sf::Text;
	g->player1uno = new sf::Text;

	g->player2bg = new sf::RectangleShape;
	g->player2name = new sf::Text;
	g->player2cards = new sf::Text;
	g->player2uno = new sf::Text;
	
	g->player3bg = new sf::RectangleShape;
	g->player3name = new sf::Text;
	g->player3cards = new sf::Text;
	g->player3uno = new sf::Text;

	g->showVeil = false;
	g->showVeilButton = false;
	
	return g;
}
void drawGame(gameManager* gm, sf::RenderWindow& window)
{

	window.draw(*(gm->sceneManager->gameUI->directionIndicator));

	window.draw(gm->sceneManager->gameUI->topCard->sprite);


	window.draw(*(gm->sceneManager->gameUI->drawCardButton));

	gm->sceneManager->gameUI->colorRedButton->setActive(gm->sceneManager->gameUI->showChangeColorUI);
	gm->sceneManager->gameUI->colorBlueButton->setActive(gm->sceneManager->gameUI->showChangeColorUI);
	gm->sceneManager->gameUI->colorGreenButton->setActive(gm->sceneManager->gameUI->showChangeColorUI);
	gm->sceneManager->gameUI->colorYellowButton->setActive(gm->sceneManager->gameUI->showChangeColorUI);

	gm->sceneManager->gameUI->yesButton->setActive(gm->sceneManager->gameUI->showPlayDrawnCardMenu);
	gm->sceneManager->gameUI->noButton->setActive(gm->sceneManager->gameUI->showPlayDrawnCardMenu);

	if (gm->sceneManager->gameUI->showChangeColorUI)
	{
		window.draw(*(gm->sceneManager->gameUI->changeColorBg));
		window.draw(*(gm->sceneManager->gameUI->changeColorLabel));
		window.draw(*(gm->sceneManager->gameUI->colorRedButton));
		window.draw(*(gm->sceneManager->gameUI->colorBlueButton));
		window.draw(*(gm->sceneManager->gameUI->colorGreenButton));
		window.draw(*(gm->sceneManager->gameUI->colorYellowButton));
	}


	if (gm->sceneManager->gameUI->showPlayDrawnCardMenu)
	{
		if (gm->sceneManager->gameUI->showOnlyCardDrawn)
		{
			window.draw(*(gm->sceneManager->gameUI->PlayDrawnMenuBg));
			window.draw(*(gm->sceneManager->gameUI->drawnCard));
		}
		else
		{
			window.draw(*(gm->sceneManager->gameUI->PlayDrawnMenuBg));
			window.draw(*(gm->sceneManager->gameUI->drawnCard));
			window.draw(*(gm->sceneManager->gameUI->drawnCardLabel));
			window.draw(*(gm->sceneManager->gameUI->yesButton));
			window.draw(*(gm->sceneManager->gameUI->noButton));
		}
	}


	//draw turnIndicator
	if (gm->game != NULL)
	{
		if (gm->sceneManager->gameUI->draw0indicator)
		{
			window.draw(*gm->sceneManager->gameUI->turnIndicator0);
		}

		if (gm->sceneManager->gameUI->draw1indicator)
		{
			window.draw(*gm->sceneManager->gameUI->turnIndicator1);
		}

		if (gm->sceneManager->gameUI->draw2indicator)
		{
			window.draw(*gm->sceneManager->gameUI->turnIndicator2);
		}

		if (gm->sceneManager->gameUI->draw3indicator)
		{
			window.draw(*gm->sceneManager->gameUI->turnIndicator3);
		}
	}



	//draw data
	if (gm->game != nullptr)
	{
		if (gm->game->playerCount >= 1)
		{
			window.draw(*(gm->sceneManager->gameUI->player0bg));
			window.draw(*(gm->sceneManager->gameUI->player0name));
			window.draw(*(gm->sceneManager->gameUI->player0cards));


			if(gm->game->players[0]->uno)
			window.draw(*(gm->sceneManager->gameUI->player0uno));
		}

		if (gm->game->playerCount >= 2)
		{
			window.draw(*(gm->sceneManager->gameUI->player1bg));
			window.draw(*(gm->sceneManager->gameUI->player1name));
			window.draw(*(gm->sceneManager->gameUI->player1cards));


			if (gm->game->players[1]->uno)
			window.draw(*(gm->sceneManager->gameUI->player1uno));
		}

		if (gm->game->playerCount >= 3)
		{
			window.draw(*(gm->sceneManager->gameUI->player2bg));
			window.draw(*(gm->sceneManager->gameUI->player2name));
			window.draw(*(gm->sceneManager->gameUI->player2cards));


			if (gm->game->players[2]->uno)
			window.draw(*(gm->sceneManager->gameUI->player2uno));
		}

		if (gm->game->playerCount >= 4)
		{
			window.draw(*(gm->sceneManager->gameUI->player3bg));
			window.draw(*(gm->sceneManager->gameUI->player3name));
			window.draw(*(gm->sceneManager->gameUI->player3cards));


			if (gm->game->players[3]->uno)
			window.draw(*(gm->sceneManager->gameUI->player3uno));
		}
	}

	//veil
	if (gm->sceneManager->gameUI->showVeil)
	{
		window.draw(*gm->sceneManager->gameUI->veil);
		window.draw(*gm->sceneManager->gameUI->veilBg);
		window.draw(*gm->sceneManager->gameUI->veilBorder0);
		window.draw(*gm->sceneManager->gameUI->veilBorder1);
		window.draw(*gm->sceneManager->gameUI->veilBorder2);
		window.draw(*gm->sceneManager->gameUI->veilBorder3);
		
		if (gm->sceneManager->gameUI->showVeilButton)
		{
			window.draw(*gm->sceneManager->gameUI->veilClose);
		}


		gm->sceneManager->gameUI->veilLabel->setPosition(sf::Vector2f(960 - gm->sceneManager->gameUI->veilLabel->getLocalBounds().width/2, 755));

		window.draw(*gm->sceneManager->gameUI->veilLabel);
	}


	//endGame
	if (gm->sceneManager->gameUI->showEndGame)
	{
		window.draw(*gm->sceneManager->gameUI->endGameBg);

		gm->sceneManager->gameUI->winnerText->setPosition(sf::Vector2f(960 - gm->sceneManager->gameUI->winnerText->getLocalBounds().width / 2, 350));

		window.draw(*gm->sceneManager->gameUI->winnerText);
		window.draw(*gm->sceneManager->gameUI->button);
	}

}


void drawGameUiBg(gameManager* gm, HandDisplay* handDisplay, sf::RenderWindow& window)
{
	//clear
	window.clear(sf::Color(6, 78, 52, 0.8));

	//draw ui

	window.draw(*(gm->sceneManager->gameUI->handBg));
	window.draw(*(gm->sceneManager->gameUI->rightSideBg));
	window.draw(*(gm->sceneManager->gameUI->horizontalLine));
	window.draw(*(gm->sceneManager->gameUI->verticalLine));
}
void drawHandDisplay(gameManager* gm, HandDisplay* handDisplay, sf::RenderWindow& window)
{
	CardButtonList* tmp = handDisplay->cardButtonList;


	while (tmp != NULL)
	{
		
		
		if (tmp->cardButton->isActive)
		{
			window.draw(*tmp->cardButton);
			tmp->cardButton->useCustomField = false;


			if (tmp->next != NULL)
			{
				if (tmp->next->cardButton->isActive)
				{
					tmp->cardButton->useCustomField = true;
					sf::FloatRect customField = sf::FloatRect(sf::Vector2f(tmp->cardButton->getPos().x - 75, tmp->cardButton->getPos().y - 100), sf::Vector2f(70, 200));
					tmp->cardButton->customField = customField;
				}

			}

			if (tmp->cardButton->position == 12 || tmp->cardButton->position == 24)
			{
				tmp->cardButton->useCustomField = false;
			}


		}


		tmp= tmp->next;

	}



}

void createPlayerDataUI(gameManager* gm)
{
	if (gm->game->playerCount >= 1)
	{
		gm->sceneManager->gameUI->player0name->setString(*gm->game->players[0]->name);
		gm->sceneManager->gameUI->player0name->setFont(*gm->font);
		gm->sceneManager->gameUI->player0name->setCharacterSize(24);
		gm->sceneManager->gameUI->player0name->setFillColor(sf::Color(212,197,10,255));

		string c = "Cards: "+to_string(listSize(gm->game->players[0]->hand));
		gm->sceneManager->gameUI->player0cards->setString(c);
		gm->sceneManager->gameUI->player0cards->setFont(*gm->font);
		gm->sceneManager->gameUI->player0cards->setCharacterSize(24);
		gm->sceneManager->gameUI->player0cards->setFillColor(sf::Color(212, 197, 10, 255));

		gm->sceneManager->gameUI->player0uno->setString("UNO!");
		gm->sceneManager->gameUI->player0uno->setFont(*gm->font);
		gm->sceneManager->gameUI->player0uno->setCharacterSize(24);
		gm->sceneManager->gameUI->player0uno->setFillColor(sf::Color::Red);


	}

	if (gm->game->playerCount >= 2)
	{
		gm->sceneManager->gameUI->player1name->setString(*gm->game->players[1]->name);
		gm->sceneManager->gameUI->player1name->setFont(*gm->font);
		gm->sceneManager->gameUI->player1name->setCharacterSize(18);
		gm->sceneManager->gameUI->player1name->setFillColor(sf::Color(212, 197, 10, 255));

		string c = "Cards: " + to_string(listSize(gm->game->players[1]->hand));
		gm->sceneManager->gameUI->player1cards->setString(c);
		gm->sceneManager->gameUI->player1cards->setFont(*gm->font);
		gm->sceneManager->gameUI->player1cards->setCharacterSize(24);
		gm->sceneManager->gameUI->player1cards->setFillColor(sf::Color(212, 197, 10, 255));

		gm->sceneManager->gameUI->player1uno->setString("UNO!");
		gm->sceneManager->gameUI->player1uno->setFont(*gm->font);
		gm->sceneManager->gameUI->player1uno->setCharacterSize(24);
		gm->sceneManager->gameUI->player1uno->setFillColor(sf::Color::Red);
	}

	if (gm->game->playerCount >= 3)
	{
		gm->sceneManager->gameUI->player2name->setString(*gm->game->players[2]->name);
		gm->sceneManager->gameUI->player2name->setFont(*gm->font);
		gm->sceneManager->gameUI->player2name->setCharacterSize(24);
		gm->sceneManager->gameUI->player2name->setFillColor(sf::Color(212, 197, 10, 255));

		string c = "Cards: " + to_string(listSize(gm->game->players[2]->hand));
		gm->sceneManager->gameUI->player2cards->setString(c);
		gm->sceneManager->gameUI->player2cards->setFont(*gm->font);
		gm->sceneManager->gameUI->player2cards->setCharacterSize(24);
		gm->sceneManager->gameUI->player2cards->setFillColor(sf::Color(212, 197, 10, 255));

		gm->sceneManager->gameUI->player2uno->setString("UNO!");
		gm->sceneManager->gameUI->player2uno->setFont(*gm->font);
		gm->sceneManager->gameUI->player2uno->setCharacterSize(24);
		gm->sceneManager->gameUI->player2uno->setFillColor(sf::Color::Red);


	}

	if (gm->game->playerCount >= 4)
	{
		gm->sceneManager->gameUI->player3name->setString(*gm->game->players[3]->name);
		gm->sceneManager->gameUI->player3name->setFont(*gm->font);
		gm->sceneManager->gameUI->player3name->setCharacterSize(18);
		gm->sceneManager->gameUI->player3name->setFillColor(sf::Color(212, 197, 10, 255));

		string c = "Cards: " + to_string(listSize(gm->game->players[3]->hand));
		gm->sceneManager->gameUI->player3cards->setString(c);
		gm->sceneManager->gameUI->player3cards->setFont(*gm->font);
		gm->sceneManager->gameUI->player3cards->setCharacterSize(24);
		gm->sceneManager->gameUI->player3cards->setFillColor(sf::Color(212, 197, 10, 255));

		gm->sceneManager->gameUI->player3uno->setString("UNO!");
		gm->sceneManager->gameUI->player3uno->setFont(*gm->font);
		gm->sceneManager->gameUI->player3uno->setCharacterSize(24);
		gm->sceneManager->gameUI->player3uno->setFillColor(sf::Color::Red);
	}

}


