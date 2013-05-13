#ifndef ENTITY_DUMMYSHIP
#define ENTITY_DUMMYSHIP
#pragma once
#include "Irrlicht\irrlicht.h"

#include "Engine/Entity.h"
#include "Engine/IrrlichtNode.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Thruster.h"
#include "Engine\Camera.h"
#include "ShipMover.h"


class DummyShip : public Entity
{
public:

	int _shipHealth;
	bool _shipDestroyed;

	bool _sitOnStation;

	void onAdd();
	void init();

	void update();
	void updateShipHealth();
	void draw();

	void CheckChangeInput();

	DummyShip(vector3df position);
	virtual ~DummyShip(void);

	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType);
	
	vector3df startPosition;
	vector3df startRotation;
private:

	Station				*_currentStation;
	matrix4				*_inertiaMatrix;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);
};
#endif