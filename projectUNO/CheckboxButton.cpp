#include "CheckboxButton.h"
#include "gameManager.h"
#include "scene.h"

void CheckboxButton::onClick(gameManager* gm)
{
	*value = !*value;
	if (*value)
	{
		setSprite(gm->textures->box_ai);
	}
	else
	{
		setSprite(gm->textures->box_human);
	}

	printf("CheckboxButton onClick! - zmiana wartosci na: %d %d %d %d\n", gm->playerType[0], gm->playerType[1], gm->playerType[2], gm->playerType[3]);
}
