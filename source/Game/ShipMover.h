#pragma once
#include "Engine\Game.h"
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "Thruster.h"
#include "CalculateRotation.h"
#include "Ship.h"
class ShipMover : public Component
{
public:
	ShipMover(Ship* ship);
	~ShipMover(void);
	void Activate();

	vector3df up;
	vector3df forward;
	vector3df right;
	void setInertiaMatrix(float h, float w, float d, float m);
	matrix4 inertiaMatrix;

	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void handleMessage(unsigned int message, void* data = 0){};

	CalculateRotation mathRotation;
	vector3df	rotationX;
	vector3df	rotationY;
	vector3df	linearAcceleration;
	vector3df	angularAcceleration;
	Ship		*_ship;

};

