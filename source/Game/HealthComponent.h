#ifndef HEALTHCOMPONENT
#define HEALTHCOMPONENT

#include "../../include/Engine/Component.h"
#include "Stations/Station.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	~HealthComponent();
	void increaseHealth(int health);
	void decreaseHealth(int health);
	void handleMessage(unsigned int message, void* data);

	//Station information
	const static int maxHealth = 100;
	int health;
};

#endif