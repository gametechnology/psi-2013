#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <stdlib.h>
#include <time.h>

static class RandomGenerator
{
public:
	static int getRandomInt(int range, int startInt);

	static float getRandomFloat(float range, float startFloat);
};

#endif