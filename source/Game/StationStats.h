#ifndef STATIONSTATS
#define STATIONSTATS

#include <Engine/Component.h>

#include "Stations/Station.h"

class StationStats : public Component
{
public:
	StationStats();
	~StationStats();
	void increaseHealth(int health);
	void increasePower(int power);
	void increaseShield(int shield);
	void decreaseHealth(int health);
	void decreasePower(int power);
	void decreaseShield(int shield);

	//Station information
	const static int maxHealth = 100;
	const static int maxPower = 100;
	const static int maxShield = 100;
	int health;
	int power;
	int shield;

};

#endif