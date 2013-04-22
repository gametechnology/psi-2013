#include "RandomGenerator.h"


int RandomGenerator::getRandomInt(int range, int startInt)
{
	srand((unsigned int)time(NULL));

	int random = rand() % range + startInt;
	return random;
}

float RandomGenerator::getRandomFloat(float range, float startFloat)
{
	srand((unsigned int)time(NULL));

	float random = startFloat + (rand() % ((int)range - 1) + (rand() / (float)RAND_MAX));
	return random;
}

