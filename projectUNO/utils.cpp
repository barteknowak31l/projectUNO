#include "utils.h"
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int randomInt(int lower, int upper)
{
	srand(time(NULL));
	int num = rand() % ((upper - lower + 1) + lower);
	return num;

}