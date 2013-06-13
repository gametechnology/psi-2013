#ifndef HEALTHCOMPONENT
#define HEALTHCOMPONENT

#include <Engine\Component.h>
#include "NetworkInterface.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	HealthComponent(int maxHealth);
	~HealthComponent();
	void increaseHealth(int health);
	void decreaseHealth(int health);
	void setHealth(int health);
	int getHealth();
	int* getPointerToHealth();
	void setMaxHealth(int maxHealth);
	int getMaxHealth();
	void handleMessage(unsigned int message, void* data);
	void updateHealthToServer();

private:
	int maxHealth_;
	int health_;
};

#endif