#include "IncrementButton.h"
#include "gameManager.h"
#include "scene.h"

void IncrementButton::onClick(gameManager* gm)
{
	*value += step;

	printf("min %d, max %d, step %d, po zmianie %d\n", min, max, step, *value);

	if (*value > max)
	{
		*value = max;
	}

	if (*value < min)
	{
		*value = min;
	}


	//wlacz pozostale przyciski
	switch (*value)
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


	printf("Increment onClick! - zmiana wartosci na: %d\n", gm->playerCount);
}