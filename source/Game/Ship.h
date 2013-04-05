#pragma once
#include "Engine\Entity.h"
#include "Thruster.h"
#include "Engine\Camera.h"
#include "HelmStation.h"
#include "WeaponStation.h"
#include "ShipMover.h"
#include "net.h"

#include "Engine\Input.h"

class Ship : public Entity
{
public:
	Ship(Composite * parent, vector3df position, vector3df rotation);
	~Ship(void);

	void update();
	void init(int station);
	void handleMessage(unsigned int message, void* data);
	void setInertiaMatrix(float h, float w, float d, float m);
	Net network;
	int stationnumber;
	Entity* currentstation;
	Input* input;
	Camera* camera;

	matrix4 inertiaMatrix;
	vector3df up;
	vector3df forward;
	vector3df right;
	Thruster* thrusters[3];
	int nrOfBullets;
	Bullet *ammo;
	int bulletNr;
	int shootingInterval;
};

