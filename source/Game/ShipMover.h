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
	void init();
	void update();
	void draw();
	void handleMessage(int message, void* data){};
private:
	vector3df totalForce;
};

