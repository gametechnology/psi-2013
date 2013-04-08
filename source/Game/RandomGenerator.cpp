#include "RandomGenerator.h"


int RandomGenerator::getRandomInt(int range, int startInt)
{
	time_t rawtime;
	time(&rawtime);

	srand(localtime(&rawtime)->tm_sec);

	int random = rand() % range + startInt;
	return random;
}

float RandomGenerator::getRandomFloat(float range, float startFloat)
{
	time_t rawtime;
	time(&rawtime);

	srand(localtime(&rawtime)->tm_sec);

	float random = startFloat + (rand() % ((int)range - 1) + (rand() / (float)RAND_MAX));
	return random;
}

