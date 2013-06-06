#ifndef SHIP_HEALTH
#define SHIP_HEALTH
#pragma once
#include "HealthComponent.h"
class Ship;

class ShipHealthComponent : public HealthComponent
{
public:
	ShipHealthComponent(Ship* ship);
	~ShipHealthComponent(void);
	void assignDamage(int damage);
	void updateHealth();
	int health;
private:
	Ship* ship_;
};
#endif

