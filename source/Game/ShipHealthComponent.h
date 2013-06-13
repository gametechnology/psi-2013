#ifndef SHIP_HEALTH
#define SHIP_HEALTH
#pragma once
#include "HealthComponent.h"
class Station;
class Ship;

class ShipHealthComponent : public HealthComponent, public INetworkListener
{
public:
	ShipHealthComponent(Ship* ship);
	~ShipHealthComponent(void);
	void assignDamage(int damage);
	void updateHealth();
	void updateHealthToServer(int stationType, int stationHealth);
	void HandleNetworkMessage(NetworkPacket packet);
	int health;
private:
	Ship* ship_;
};
#endif

