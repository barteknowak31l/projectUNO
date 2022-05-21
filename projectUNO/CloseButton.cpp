#include "CloseButton.h"

#include "scene.h"



void CloseButton::onClick(gameManager* gm)
{
	printf("CloseButtonOnclick: zamykam veil");
	gm->sceneManager->gameUI->showVeil = false;
		
}