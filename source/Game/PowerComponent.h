#ifndef POWERCOMPONENT
#define POWERCOMPONENT

#include "../../include/Engine/Component.h"
#include "Stations/Station.h"

class PowerComponent : public Component
{
public:
	PowerComponent();
	~PowerComponent();
	void increasePower(int power);
	void decreasePower(int power);

	//Station information
	const static int maxPower = 100;
	int power;
};

#endif