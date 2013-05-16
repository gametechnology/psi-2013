#ifndef STATIONSTATS
#define STATIONSTATS

#include "../../include/Engine/Component.h"
#include "Stations/Station.h"

class StationStats : public Component
{
public:
	StationStats();
	~StationStats();

	//Station information
	const static int maxHealth = 100;
	int health;
	int power;
	int shield;

};

#endif