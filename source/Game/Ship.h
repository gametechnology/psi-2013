#pragma once
#include "Engine\Entity.h"
#include "Thruster.h"
#include "Engine\Camera.h"
#include "HelmStation.h"
#include "WeaponStation.h"
#include "ShipMover.h"
#include "net.h"

class Ship : public Entity
{
public:
	Ship(Composite * parent, vector3df position, vector3df rotation);
	Ship(Composite * parent);
	~Ship(void);

	void update();
	void init(int station);
	void handleMessage(unsigned int message, void* data);
	Net network;
	Entity* currentstation;
	Camera* camera;
	float drag;
	Thruster* thrusters[3];
};

