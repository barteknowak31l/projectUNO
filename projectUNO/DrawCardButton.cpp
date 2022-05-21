#include "DrawCardButton.h"
#include "scene.h"


void DrawCardButton::onClick(gameManager* gm)
{
	if (size(gm->game->deck) == 0)
	{
		return;
	}

	if (gm->game->players[gm->game->turn]->playerDidAnAction == false)
	{
		gm->game->players[gm->game->turn]->playerDidAnAction = true;
		card* c = drawCard(gm->game, gm->game->turn);
		printf("DrawCardOnClick: gracz: %d dobiera karte ", gm->game->turn);
		getCardFromId(c->id);

		if (checkCardCorrect(c, gm->game->cardsPlayed) || isBlackCard(c))
		{
			reshuffle(gm->game);
			gm->sceneManager->gameUI->showPlayDrawnCardMenu = true;
			gm->sceneManager->gameUI->drawnCard->setTexture(*(c)->texture);
			//playDrawnCard(gm->game);
			//gm->startTurn = 1;
			return;

		}

		gm->sceneManager->gameUI->showPlayDrawnCardMenu = true;
		gm->sceneManager->gameUI->showOnlyCardDrawn = true;
		gm->sceneManager->gameUI->drawnCard->setTexture(*(c)->texture);

		nextTurn(gm->game);
		gm->startTurn = 1;
	}

}