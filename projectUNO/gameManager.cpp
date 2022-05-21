#include "gameManager.h"
#include "player.h"
#include "mcts.h"
#include <stdlib.h>
#include <SFML/Graphics.hpp>

#include "scene.h"


struct gameManager ga;

gameManager* createGameManager()
{
	gameManager* g = (gameManager*)malloc(sizeof(gameManager));


	loadTextures(g);
	
	//gra tworzy sie pozniej
	g->game = NULL;

	g->playerCount = 2;
	g->playerType[0] = 0;
	g->playerType[1] = 0;
	g->playerType[2] = 0;
	g->playerType[3] = 0;

	g->sceneManager = createSceneManager();
	g->exitGame = 0;

	g->mctsDepth = 0;
	g->mctsSimDepth = 0;


	g->waitTime = 0;
	g->currentWaitTime = 0;

	g->startTurn = true;


	g->waitTime = 1.5;
	g->currentWaitTime = g->waitTime + 1;

	setupMCTS(g, 50, 10);


	return g;
}


void loadTextures(gameManager* g)
{
	g->textures = (Textures*)malloc(sizeof(Textures));

	sf::Texture* checkbox_no = new sf::Texture;
	checkbox_no->loadFromFile("textures/UI/checkbox_no.png");
	sf::Texture* checkbox_yes = new sf::Texture;
	checkbox_yes->loadFromFile("textures/UI/checkbox_yes.png");


	g->textures->checkbox_no = checkbox_no;
	g->textures->checkbox_yes = checkbox_yes;

	g->textures->cardTextures = (CardTextures*)malloc(sizeof(CardTextures));

	g->font = new sf::Font;
	g->font->loadFromFile("textures/fonts/SHOWG.TTF");

	g->textures->turnIndicator = new sf::Texture;
	g->textures->turnIndicator->loadFromFile("textures/UI/turnIndicator.png");

	g->textures->directionIndicator = new sf::Texture;
	g->textures->directionIndicator->loadFromFile("textures/UI/directionIndicator.png");
	g->textures->directionIndicatorReversed = new sf::Texture;
	g->textures->directionIndicatorReversed->loadFromFile("textures/UI/directionIndicatorReversed.png");

	sf::Texture* logo = new sf::Texture;
	logo->loadFromFile("textures/logo.png");
	g->textures->logo = logo;

	sf::Texture* box_ai = new sf::Texture;
	box_ai->loadFromFile("textures/UI/box_ai.png");
	g->textures->box_ai = box_ai;

	sf::Texture* box_human = new sf::Texture;
	box_human->loadFromFile("textures/UI/box_human.png");
	g->textures->box_human = box_human;

	sf::Texture* btn_play = new sf::Texture();
	btn_play->loadFromFile("textures/UI/btn_play.png");
	g->textures->btn_play = btn_play;

	sf::Texture* btn_exit = new sf::Texture();
	btn_exit->loadFromFile("textures/UI/btn_exit.png");
	g->textures->btn_exit = btn_exit;

	sf::Texture* playersLabel = new sf::Texture();
	playersLabel->loadFromFile("textures/UI/players_label.png");
	g->textures->playersLabel = playersLabel;

	sf::Texture* player1Label = new sf::Texture();
	player1Label->loadFromFile("textures/UI/player1_name_label.png");
	g->textures->player1Label = player1Label;

	sf::Texture* player2Label = new sf::Texture();
	player2Label->loadFromFile("textures/UI/player2_name_label.png");
	g->textures->player2Label = player2Label;

	sf::Texture* player3Label = new sf::Texture();
	player3Label->loadFromFile("textures/UI/player3_name_label.png");
	g->textures->player3Label = player3Label;

	sf::Texture* player4Label = new sf::Texture();
	player4Label->loadFromFile("textures/UI/player4_name_label.png");
	g->textures->player4Label = player4Label;

	sf::Texture* emptyLabel = new sf::Texture();
	emptyLabel->loadFromFile("textures/UI/empty_label.png");
	g->textures->emptyLabel = emptyLabel;

	sf::Texture* box_plus = new sf::Texture();
	box_plus->loadFromFile("textures/UI/box_plus.png");
	g->textures->box_plus = box_plus;

	sf::Texture* box_minus = new sf::Texture();
	box_minus->loadFromFile("textures/UI/box_minus.png");
	g->textures->box_minus = box_minus;

	sf::Image* icon = new sf::Image;
	icon->loadFromFile("textures/icon.png");
	g->textures->icon = icon;

	sf::Image* cur = new sf::Image;
	cur->loadFromFile("textures/cursor.png");
	g->textures->cur = cur;

	sf::Image* cur_cl = new sf::Image;
	cur_cl->loadFromFile("textures/cursor_pressed.png");
	g->textures->cur_cl = cur_cl;

	sf::Cursor* cursor = new sf::Cursor;
	cursor->loadFromPixels(g->textures->cur->getPixelsPtr(),g->textures->cur->getSize(), sf::Vector2u(0, 0));
	g->textures->cursor = cursor;




#pragma region cardTextures

	sf::Texture* emptyCard = new sf::Texture;

	sf::Texture* red0 = new sf::Texture;
	sf::Texture* red1 = new sf::Texture;
	sf::Texture* red2 = new sf::Texture;
	sf::Texture* red3 = new sf::Texture;
	sf::Texture* red4 = new sf::Texture;
	sf::Texture* red5 = new sf::Texture;
	sf::Texture* red6 = new sf::Texture;
	sf::Texture* red7 = new sf::Texture;
	sf::Texture* red8 = new sf::Texture;
	sf::Texture* red9 = new sf::Texture;
	sf::Texture* redPlus2 = new sf::Texture;
	sf::Texture* redReverse = new sf::Texture;
	sf::Texture* redStop = new sf::Texture;

	sf::Texture* blue0 = new sf::Texture;
	sf::Texture* blue1 = new sf::Texture;
	sf::Texture* blue2 = new sf::Texture;
	sf::Texture* blue3 = new sf::Texture;
	sf::Texture* blue4 = new sf::Texture;
	sf::Texture* blue5 = new sf::Texture;
	sf::Texture* blue6 = new sf::Texture;
	sf::Texture* blue7 = new sf::Texture;
	sf::Texture* blue8 = new sf::Texture;
	sf::Texture* blue9 = new sf::Texture;
	sf::Texture* bluePlus2 = new sf::Texture;
	sf::Texture* blueReverse = new sf::Texture;
	sf::Texture* blueStop = new sf::Texture;

	sf::Texture* green0 = new sf::Texture;
	sf::Texture* green1 = new sf::Texture;
	sf::Texture* green2 = new sf::Texture;
	sf::Texture* green3 = new sf::Texture;
	sf::Texture* green4 = new sf::Texture;
	sf::Texture* green5 = new sf::Texture;
	sf::Texture* green6 = new sf::Texture;
	sf::Texture* green7 = new sf::Texture;
	sf::Texture* green8 = new sf::Texture;
	sf::Texture* green9 = new sf::Texture;
	sf::Texture* greenPlus2 = new sf::Texture;
	sf::Texture* greenReverse = new sf::Texture;
	sf::Texture* greenStop = new sf::Texture;

	sf::Texture* yellow0 = new sf::Texture;
	sf::Texture* yellow1 = new sf::Texture;
	sf::Texture* yellow2 = new sf::Texture;
	sf::Texture* yellow3 = new sf::Texture;
	sf::Texture* yellow4 = new sf::Texture;
	sf::Texture* yellow5 = new sf::Texture;
	sf::Texture* yellow6 = new sf::Texture;
	sf::Texture* yellow7 = new sf::Texture;
	sf::Texture* yellow8 = new sf::Texture;
	sf::Texture* yellow9 = new sf::Texture;
	sf::Texture* yellowPlus2 = new sf::Texture;
	sf::Texture* yellowReverse = new sf::Texture;
	sf::Texture* yellowStop = new sf::Texture;


	sf::Texture* blackColor = new sf::Texture;
	sf::Texture* blackColorRed = new sf::Texture;
	sf::Texture* blackColorBlue = new sf::Texture;
	sf::Texture* blackColorGreen = new sf::Texture;
	sf::Texture* blackColorYellow = new sf::Texture;

	sf::Texture* blackColorPlus4 = new sf::Texture;
	sf::Texture* blackColorPlus4red = new sf::Texture;
	sf::Texture* blackColorPlus4blue = new sf::Texture;
	sf::Texture* blackColorPlus4green = new sf::Texture;
	sf::Texture* blackColorPlus4yellow = new sf::Texture;

	sf::Texture* changeColorLabelTexture = new sf::Texture;
	sf::Texture* colorRedButtonTexture = new sf::Texture;
	sf::Texture* colorBlueButtonTexture = new sf::Texture;
	sf::Texture* colorGreenButtonTexture = new sf::Texture;
	sf::Texture* colorYellowButtonTexture = new sf::Texture;

	sf::Texture* drawCardButtonTexture = new sf::Texture;

	sf::Texture* playInstantLabel = new sf::Texture;

	emptyCard->loadFromFile("textures/cards/emptyCard.png");

	red0->loadFromFile("textures/cards/red/red0.png");
	red1->loadFromFile("textures/cards/red/red1.png");
	red2->loadFromFile("textures/cards/red/red2.png");
	red3->loadFromFile("textures/cards/red/red3.png");
	red4->loadFromFile("textures/cards/red/red4.png");
	red5->loadFromFile("textures/cards/red/red5.png");
	red6->loadFromFile("textures/cards/red/red6.png");
	red7->loadFromFile("textures/cards/red/red7.png");
	red8->loadFromFile("textures/cards/red/red8.png");
	red9->loadFromFile("textures/cards/red/red9.png");
	redPlus2->loadFromFile("textures/cards/red/redPlus2.png");
	redReverse->loadFromFile("textures/cards/red/redReverse.png");
	redStop->loadFromFile("textures/cards/red/redStop.png");

	blue0->loadFromFile("textures/cards/blue/blue0.png");
	blue1->loadFromFile("textures/cards/blue/blue1.png");
	blue2->loadFromFile("textures/cards/blue/blue2.png");
	blue3->loadFromFile("textures/cards/blue/blue3.png");
	blue4->loadFromFile("textures/cards/blue/blue4.png");
	blue5->loadFromFile("textures/cards/blue/blue5.png");
	blue6->loadFromFile("textures/cards/blue/blue6.png");
	blue7->loadFromFile("textures/cards/blue/blue7.png");
	blue8->loadFromFile("textures/cards/blue/blue8.png");
	blue9->loadFromFile("textures/cards/blue/blue9.png");
	bluePlus2->loadFromFile("textures/cards/blue/bluePlus2.png");
	blueReverse->loadFromFile("textures/cards/blue/blueReverse.png");
	blueStop->loadFromFile("textures/cards/blue/blueStop.png");

	green0->loadFromFile("textures/cards/green/green0.png");
	green1->loadFromFile("textures/cards/green/green1.png");
	green2->loadFromFile("textures/cards/green/green2.png");
	green3->loadFromFile("textures/cards/green/green3.png");
	green4->loadFromFile("textures/cards/green/green4.png");
	green5->loadFromFile("textures/cards/green/green5.png");
	green6->loadFromFile("textures/cards/green/green6.png");
	green7->loadFromFile("textures/cards/green/green7.png");
	green8->loadFromFile("textures/cards/green/green8.png");
	green9->loadFromFile("textures/cards/green/green9.png");
	greenPlus2->loadFromFile("textures/cards/green/greenPlus2.png");
	greenReverse->loadFromFile("textures/cards/green/greenReverse.png");
	greenStop->loadFromFile("textures/cards/green/greenStop.png");

	yellow0->loadFromFile("textures/cards/yellow/yellow0.png");
	yellow1->loadFromFile("textures/cards/yellow/yellow1.png");
	yellow2->loadFromFile("textures/cards/yellow/yellow2.png");
	yellow3->loadFromFile("textures/cards/yellow/yellow3.png");
	yellow4->loadFromFile("textures/cards/yellow/yellow4.png");
	yellow5->loadFromFile("textures/cards/yellow/yellow5.png");
	yellow6->loadFromFile("textures/cards/yellow/yellow6.png");
	yellow7->loadFromFile("textures/cards/yellow/yellow7.png");
	yellow8->loadFromFile("textures/cards/yellow/yellow8.png");
	yellow9->loadFromFile("textures/cards/yellow/yellow9.png");
	yellowPlus2->loadFromFile("textures/cards/yellow/yellowPlus2.png");
	yellowReverse->loadFromFile("textures/cards/yellow/yellowReverse.png");
	yellowStop->loadFromFile("textures/cards/yellow/yellowStop.png");

	blackColor->loadFromFile("textures/cards/black/blackColor.png");
	blackColorRed->loadFromFile("textures/cards/black/blackColorRed.png");
	blackColorBlue->loadFromFile("textures/cards/black/blackColorBlue.png");
	blackColorGreen->loadFromFile("textures/cards/black/blackColorGreen.png");
	blackColorYellow->loadFromFile("textures/cards/black/blackColorYellow.png");

	blackColorPlus4->loadFromFile("textures/cards/black/blackColorPlus4.png");
	blackColorPlus4red->loadFromFile("textures/cards/black/blackColorPlus4red.png");
	blackColorPlus4blue->loadFromFile("textures/cards/black/blackColorPlus4blue.png");
	blackColorPlus4green->loadFromFile("textures/cards/black/blackColorPlus4green.png");
	blackColorPlus4yellow->loadFromFile("textures/cards/black/blackColorPlus4yellow.png");

	changeColorLabelTexture->loadFromFile("textures/UI/ChooseColor/chooseColorLabel.png");
	colorRedButtonTexture->loadFromFile("textures/UI/ChooseColor/red.png");
	colorBlueButtonTexture->loadFromFile("textures/UI/ChooseColor/blue.png");
	colorGreenButtonTexture->loadFromFile("textures/UI/ChooseColor/green.png");
	colorYellowButtonTexture->loadFromFile("textures/UI/ChooseColor/yellow.png");

	drawCardButtonTexture->loadFromFile("textures/UI/drawCardButton.png");

	playInstantLabel->loadFromFile("textures/UI/playInstantLabel.png");


	g->textures->cardTextures->emptyCard = emptyCard;

	g->textures->cardTextures->red0 = red0;
	g->textures->cardTextures->red1 = red1;
	g->textures->cardTextures->red2 = red2;
	g->textures->cardTextures->red3 = red3;
	g->textures->cardTextures->red4 = red4;
	g->textures->cardTextures->red5 = red5;
	g->textures->cardTextures->red6 = red6;
	g->textures->cardTextures->red7 = red7;
	g->textures->cardTextures->red8 = red8;
	g->textures->cardTextures->red9 = red9;
	g->textures->cardTextures->redPlus2 = redPlus2;
	g->textures->cardTextures->redReverse = redReverse;
	g->textures->cardTextures->redStop = redStop;

	g->textures->cardTextures->blue0 = blue0;
	g->textures->cardTextures->blue1 = blue1;
	g->textures->cardTextures->blue2 = blue2;
	g->textures->cardTextures->blue3 = blue3;
	g->textures->cardTextures->blue4 = blue4;
	g->textures->cardTextures->blue5 = blue5;
	g->textures->cardTextures->blue6 = blue6;
	g->textures->cardTextures->blue7 = blue7;
	g->textures->cardTextures->blue8 = blue8;
	g->textures->cardTextures->blue9 = blue9;
	g->textures->cardTextures->bluePlus2 = bluePlus2;
	g->textures->cardTextures->blueReverse = blueReverse;
	g->textures->cardTextures->blueStop = blueStop;

	g->textures->cardTextures->green0 = green0;
	g->textures->cardTextures->green1 = green1;
	g->textures->cardTextures->green2 = green2;
	g->textures->cardTextures->green3 = green3;
	g->textures->cardTextures->green4 = green4;
	g->textures->cardTextures->green5 = green5;
	g->textures->cardTextures->green6 = green6;
	g->textures->cardTextures->green7 = green7;
	g->textures->cardTextures->green8 = green8;
	g->textures->cardTextures->green9 = green9;
	g->textures->cardTextures->greenPlus2 = greenPlus2;
	g->textures->cardTextures->greenReverse = greenReverse;
	g->textures->cardTextures->greenStop = greenStop;

	g->textures->cardTextures->yellow0 = yellow0;
	g->textures->cardTextures->yellow1 = yellow1;
	g->textures->cardTextures->yellow2 = yellow2;
	g->textures->cardTextures->yellow3 = yellow3;
	g->textures->cardTextures->yellow4 = yellow4;
	g->textures->cardTextures->yellow5 = yellow5;
	g->textures->cardTextures->yellow6 = yellow6;
	g->textures->cardTextures->yellow7 = yellow7;
	g->textures->cardTextures->yellow8 = yellow8;
	g->textures->cardTextures->yellow9 = yellow9;
	g->textures->cardTextures->yellowPlus2 = yellowPlus2;
	g->textures->cardTextures->yellowReverse = yellowReverse;
	g->textures->cardTextures->yellowStop = yellowStop;

	g->textures->cardTextures->blackColor = blackColor;
	g->textures->cardTextures->blackColorRed = blackColorRed;
	g->textures->cardTextures->blackColorBlue = blackColorBlue;
	g->textures->cardTextures->blackColorGreen = blackColorGreen;
	g->textures->cardTextures->blackColorYellow = blackColorYellow;

	g->textures->cardTextures->blackColorPlus4 = blackColorPlus4;
	g->textures->cardTextures->blackColorPlus4red = blackColorPlus4red;
	g->textures->cardTextures->blackColorPlus4blue = blackColorPlus4blue;
	g->textures->cardTextures->blackColorPlus4green = blackColorPlus4green;
	g->textures->cardTextures->blackColorPlus4yellow = blackColorPlus4yellow;

	g->textures->changeColorLabelTexture = changeColorLabelTexture;
	g->textures->colorRedButtonTexture = colorRedButtonTexture;
	g->textures->colorBlueButtonTexture = colorBlueButtonTexture;
	g->textures->colorGreenButtonTexture = colorGreenButtonTexture;
	g->textures->colorYellowButtonTexture = colorYellowButtonTexture;

	g->textures->drawCardButtonTexture = drawCardButtonTexture;

	g->textures->playInstantLabel = playInstantLabel;


#pragma endregion
}

void setupMCTS(gameManager* gm,int d, int sd)
{
	gm->mctsDepth = d;
	gm->mctsSimDepth = sd;
}

void createPlayers(gameManager* gm, game* g)
{
	g->players = (player**)malloc(sizeof(player*) * (gm->playerCount));

	std::string n;

	for (int i = 0; i < gm->playerCount; i++)
	{
		switch (i)
		{
		case 0 :
		{
			n = gm->player0text->getText();
			if (n.length() == 0)
			{
				n = "player1";
			}
			break;
		}
		case 1:
		{
			n = gm->player1text->getText();
			if (n.length() == 0)
			{
				n = "player2";
			}
			break;
		}
		case 2:
		{
			n = gm->player2text->getText();
			if (n.length() == 0)
			{
				n = "player3";
			}
			break;
		}
		case 3:
		{
			n = gm->player3text->getText();
			if (n.length() == 0)
			{
				n = "player4";
			}
			break;
		}
		}


		g->players[i] = createPlayer(i, gm->playerType[i],n);


	}



}

game* createGame(gameManager* gm, int startingHandSize)
{
	
	game* g = new game;

	g->gm = gm;

	g->newColorOfCard = 0;
	g->newColorOfCardPosition = 0;
	g->playerClickedYesNo = false;

	g->currentScene = 0;

	g->playerCount = gm->playerCount;
	g->startingHandSize = startingHandSize;
	g->turn = 0;
	g->playDirection = 1;
	g->gameStarted = false;
	g->skipTurn = 0;


	//create players
	createPlayers(gm,g);
	//generate starting deck
	g->deck = generateStartingDeck();

	//dodaj tekstury kart
	setCardTextures(gm, g->deck);

	//generate pile of played cards
	g->cardsPlayed = createStack();
	
	//tasowanie
	shuffle(&g->deck);
	shuffle(&g->deck);
	shuffle(&g->deck);

	//poloz pierwsza karte na stosie zagranych:
	putCardOnTop(g);
	dealTheCards(g);


	g->gameStarted = true;
	return g;

}

void dealTheCards(game* g)
{
	for (int i = 0; i < g->playerCount; i++)
	{
		g->turn = i;
		for (int j = 0; j<g->startingHandSize; j++)
		{
			drawCard(g,i);
		}
		sortList(g->players[i]->hand);
	}



	g->turn = 0;

}

void nextTurn(game* g)
{
	g->turn = g->turn + g->playDirection;

	if (g->turn >= g->playerCount)
		g->turn = 0;

	if (g->turn < 0)
		g->turn = g->playerCount - 1;


	g->gm->currentWaitTime = 0;

}

int nextPlayerId(game* g)
{
	int id = g->turn + g->playDirection;

	if (id >= g->playerCount)
		id = 0;

	if (id < 0)
		id = g->playerCount - 1;

	return id;
}

void changeScene(game* g, int scene)
{
	g->currentScene = scene;
}


game* deleteGame(game* g)
{
	for (int i = 0; i < g->playerCount; i++)
	{
		deletePlayer(g->players[i]);
	}
	destroyStack(&g->deck);
	destroyStack(&g->cardsPlayed);

	g = NULL;
	return g;

}

void setCardTextures(gameManager* gm,stack* cards)
{
	stack* tmp = cards;
	int c = 0;
	int v = 0;


	while (tmp != NULL)
	{
		c = getCardColorID(tmp->c->id);
		v = getCardValueID(tmp->c->id);

		if (c == red)
		{
			if (v == 0)
			{
				tmp->c->texture = gm->textures->cardTextures->red0;
			}

			if (v == 1)
			{
				tmp->c->texture = gm->textures->cardTextures->red1;
			}

			if (v == 2)
			{
				tmp->c->texture = gm->textures->cardTextures->red2;
			}

			if (v == 3)
			{
				tmp->c->texture = gm->textures->cardTextures->red3;
			}

			if (v == 4)
			{
				tmp->c->texture = gm->textures->cardTextures->red4;
			}

			if (v == 5)
			{
				tmp->c->texture = gm->textures->cardTextures->red5;
			}

			if (v == 6)
			{
				tmp->c->texture = gm->textures->cardTextures->red6;
			}

			if (v == 7)
			{
				tmp->c->texture = gm->textures->cardTextures->red7;
			}

			if (v == 8)
			{
				tmp->c->texture = gm->textures->cardTextures->red8;
			}

			if (v == 9)
			{
				tmp->c->texture = gm->textures->cardTextures->red9;
			}

			if (v == draw2)
			{
				tmp->c->texture = gm->textures->cardTextures->redPlus2;
			}

			if (v == changeDir)
			{
				tmp->c->texture = gm->textures->cardTextures->redReverse;
			}

			if (v == stop)
			{
				tmp->c->texture = gm->textures->cardTextures->redStop;
			}
		}

		if (c == blue)
		{
			if (v == 0)
			{
				tmp->c->texture = gm->textures->cardTextures->blue0;
			}

			if (v == 1)
			{
				tmp->c->texture = gm->textures->cardTextures->blue1;
			}

			if (v == 2)
			{
				tmp->c->texture = gm->textures->cardTextures->blue2;
			}

			if (v == 3)
			{
				tmp->c->texture = gm->textures->cardTextures->blue3;
			}

			if (v == 4)
			{
				tmp->c->texture = gm->textures->cardTextures->blue4;
			}

			if (v == 5)
			{
				tmp->c->texture = gm->textures->cardTextures->blue5;
			}

			if (v == 6)
			{
				tmp->c->texture = gm->textures->cardTextures->blue6;
			}

			if (v == 7)
			{
				tmp->c->texture = gm->textures->cardTextures->blue7;
			}

			if (v == 8)
			{
				tmp->c->texture = gm->textures->cardTextures->blue8;
			}

			if (v == 9)
			{
				tmp->c->texture = gm->textures->cardTextures->blue9;
			}

			if (v == draw2)
			{
				tmp->c->texture = gm->textures->cardTextures->bluePlus2;
			}

			if (v == changeDir)
			{
				tmp->c->texture = gm->textures->cardTextures->blueReverse;
			}

			if (v == stop)
			{
				tmp->c->texture = gm->textures->cardTextures->blueStop;
			}
		}

		if (c == green)
		{
			if (v == 0)
			{
				tmp->c->texture = gm->textures->cardTextures->green0;
			}

			if (v == 1)
			{
				tmp->c->texture = gm->textures->cardTextures->green1;
			}

			if (v == 2)
			{
				tmp->c->texture = gm->textures->cardTextures->green2;
			}

			if (v == 3)
			{
				tmp->c->texture = gm->textures->cardTextures->green3;
			}

			if (v == 4)
			{
				tmp->c->texture = gm->textures->cardTextures->green4;
			}

			if (v == 5)
			{
				tmp->c->texture = gm->textures->cardTextures->green5;
			}

			if (v == 6)
			{
				tmp->c->texture = gm->textures->cardTextures->green6;
			}

			if (v == 7)
			{
				tmp->c->texture = gm->textures->cardTextures->green7;
			}

			if (v == 8)
			{
				tmp->c->texture = gm->textures->cardTextures->green8;
			}

			if (v == 9)
			{
				tmp->c->texture = gm->textures->cardTextures->green9;
			}

			if (v == draw2)
			{
				tmp->c->texture = gm->textures->cardTextures->greenPlus2;
			}

			if (v == changeDir)
			{
				tmp->c->texture = gm->textures->cardTextures->greenReverse;
			}

			if (v == stop)
			{
				tmp->c->texture = gm->textures->cardTextures->greenStop;
			}
		}

		if (c == yellow)
		{
			if (v == 0)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow0;
			}

			if (v == 1)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow1;
			}

			if (v == 2)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow2;
			}

			if (v == 3)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow3;
			}

			if (v == 4)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow4;
			}

			if (v == 5)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow5;
			}

			if (v == 6)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow6;
			}

			if (v == 7)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow7;
			}

			if (v == 8)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow8;
			}

			if (v == 9)
			{
				tmp->c->texture = gm->textures->cardTextures->yellow9;
			}

			if (v == draw2)
			{
				tmp->c->texture = gm->textures->cardTextures->yellowPlus2;
			}

			if (v == changeDir)
			{
				tmp->c->texture = gm->textures->cardTextures->yellowReverse;
			}

			if (v == stop)
			{
				tmp->c->texture = gm->textures->cardTextures->yellowStop;
			}
		}


		//black:

		if (c == red)
		{
			if (v == changeCol)
			{
				tmp->c->texture = gm->textures->cardTextures->blackColor;
			}

			if (v == changeColDraw4)
			{
				tmp->c->texture = gm->textures->cardTextures->blackColorPlus4;
			}
		}

		tmp= tmp->next;
	}
}
