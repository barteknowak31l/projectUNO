#include "YesNoButton.h"
#include "scene.h"


void YesNoButton::onClick(gameManager* gm)
{

	if (gm->game->playerClickedYesNo)
	{
		return;
	}

	if (value)
	{
		if (!(getCardValueID(gm->game->players[gm->game->turn]->hand->c->id) == 13 || getCardValueID(gm->game->players[gm->game->turn]->hand->c->id) == 14))
		{
			playCard(gm->game, 1);
			gm->game->players[gm->game->turn]->playerDidAnAction = true;
			gm->sceneManager->gameUI->showPlayDrawnCardMenu = false;
			gm->game->playerClickedYesNo = true;
			gm->startTurn = true;
			printf("YES onClick! - zagrywam dobrana karte\n");
			return;
		}
		else
		{
			gm->game->newColorOfCardPosition = 1;
			gm->startTurn = 0;
			gm->game->players[gm->game->turn]->playerDidAnAction = true;
			gm->sceneManager->gameUI->showChangeColorUI = true;
			gm->game->playerClickedYesNo = true;

			printf("YES onClick! - zagrywam dobrana karte\n");
			return;
		}

	}
	printf("NO onClick! -  nie zagrywam dobranej karty\n");

	printf("sortuje liste %d z YESNO\n",gm->game->turn);
	sortList(gm->game->players[gm->game->turn]->hand);

	gm->game->players[gm->game->turn]->playerDidAnAction = true;
	gm->startTurn = true;
	nextTurn(gm->game);
	gm->sceneManager->gameUI->showPlayDrawnCardMenu = false;

}