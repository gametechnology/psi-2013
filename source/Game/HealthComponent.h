#ifndef HEALTHCOMPONENT
#define HEALTHCOMPONENT

#include <Engine/Component.h>
#include "Messages.h"

class Station;

class HealthComponent : public Component
{
public:
	const int maxHealth;
	int health;

	HealthComponent();
	virtual ~HealthComponent();

	void increaseHealth(int health);
	void decreaseHealth(int health);
	void handleMessage(unsigned int message, void* data);
};

#endif