#pragma once
#include "Engine\Game.h"
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "Thruster.h"
#include "CalculateRotation.h"
class ShipMover : public Component
{
public:
	ShipMover(Composite* parent, Thruster* thrusters[]);
	~ShipMover(void);
	void Activate();

	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void handleMessage(unsigned int message, void* data = 0){};

	float h, w, d, m;

	CalculateRotation mathRotation;
	vector3df rotationX;
	vector3df rotationY;
	vector3df linearAcceleration;
	vector3df angularAcceleration;
private:
	Thruster** thrusters;

};

