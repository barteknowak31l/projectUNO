#include "ChooseColorButton.h"
#include "scene.h"
#include "player.h"

void ChooseColorButton::onClick(gameManager* gm)
{
	gm->game->newColorOfCard = color;
	playCard(gm->game, gm->game->newColorOfCardPosition);
	gm->sceneManager->gameUI->showChangeColorUI = false;
	gm->startTurn = 1;

}