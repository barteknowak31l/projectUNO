#include "ExitButton.h"
#include "gameManager.h"
#include "scene.h"

void ExitButton::onClick(gameManager* gm)
{
	gm->exitGame = 1;
	printf("ExitButton onClick! - koniec programu\n");
}