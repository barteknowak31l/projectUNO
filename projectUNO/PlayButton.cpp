#include "PlayButton.h"
#include "gameManager.h"
#include "scene.h"



void PlayButton::onClick(gameManager* gm)
{
	int i = gm->sceneManager->currentScene;
	i++;
	if (i > 2)
	{
		i = 0;
	}
	gm->sceneManager->currentScene = i;
	
	printf("playButton onClick! - zmiana sceny na: %d\n",i);
}