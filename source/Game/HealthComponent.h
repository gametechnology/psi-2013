#ifndef HEALTHCOMPONENT
#define HEALTHCOMPONENT

#include <Engine/Component.h>

#include "Stations/Station.h"
#include "Messages.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	virtual ~HealthComponent();

	void increaseHealth(int health);
	void decreaseHealth(int health);
	void handleMessage(unsigned int message, void* data);

private:
	const int maxHealth = 100;
	int health;
};

#endif