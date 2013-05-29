#ifndef POWERCOMPONENT
#define POWERCOMPONENT

#include <Engine/Component.h>

#include "Messages.h"

class Station;

class PowerComponent : public Component
{
public:
	PowerComponent();
	~PowerComponent();
	void increasePower(int power);
	void decreasePower(int power);
	void handleMessage(unsigned int message, void* data);

	//Station information
	const static int maxPower = 100;
	int power;
};

#endif