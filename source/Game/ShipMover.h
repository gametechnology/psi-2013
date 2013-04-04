#pragma once
#include "Engine\Game.h"
#include "Engine\Component.h"
#include "Irrlicht\irrlicht.h"
#include "Thruster.h"
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
private:
	Thruster** thrusters;
	vector3df totalForce;
};

