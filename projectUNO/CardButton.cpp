#include "CardButton.h"
#include "gameManager.h"
#include "scene.h"
#include "player.h"

void CardButton::onClick(gameManager* gm)
{
	printf("cardButtonID : %d", card->id);
	getCardFromId(card->id);


	if ((checkCardCorrect(card, gm->game->cardsPlayed) || isBlackCard(card)) && gm->game->players[gm->game->turn]->comp == false && gm->game->players[gm->game->turn]->playerDidAnAction == false)
	{
		if (!( getCardValueID(card->id)== 13 || getCardValueID(card->id) == 14 ) )
		{
			playCard(gm->game, position);
			gm->game->players[gm->game->turn]->playerDidAnAction = true;
			printf("CardButton onClick! - zagrywam karte na pozycji %d, id: %d\n", position, card->id);
			gm->startTurn = true;

			setSprite(gm->textures->cardTextures->emptyCard);


		}
		else
		{
			setSprite(gm->textures->cardTextures->emptyCard);
			gm->game->newColorOfCardPosition = position;
			gm->game->players[gm->game->turn]->playerDidAnAction = true;
			gm->sceneManager->gameUI->showChangeColorUI = true;
		}


	}


}



