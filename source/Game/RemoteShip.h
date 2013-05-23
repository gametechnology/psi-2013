#ifndef REMOTE_SHIP
#define REMOTE_SHIP
#pragma once

#include "Irrlicht\irrlicht.h"

#include "Engine/Entity.h"
#include "Engine/IrrlichtNode.h"
#include "Player.h"
#include "Thruster.h"
#include "ShipMover.h"
#include "Laser.h"

class RemoteShip : public Entity
{
public:

	bool _shipDestroyed;

	bool _sitOnStation;

	void onAdd();
	void init();

	void update();
	void draw();

	RemoteShip(vector3df position, vector3df rotation);
	virtual ~RemoteShip(void);

	Thruster**	GetThrusters();

	int getShipHealth();
	bool getShipDestroyed();
	
	void fireLaser();
private:

	Thruster			*_thrusters[4];
	matrix4				*_inertiaMatrix;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);

	vector<Laser*> _laser;
	int _laserCount, _laserCounter;
};
#endif
