/* 
* Basic ship mover, does not use thrusters.
*/

#pragma once
#include "BasicMoverComponent.h"
#include "Ship.h"

class BasicShipMover : public BasicMoverComponent
{
public:
	BasicShipMover(Ship* ship);
	~BasicShipMover();

	virtual void update();
	virtual void handleMessage(unsigned int message, void* data = 0){};
	void setMaxSpeed(float speed);
private:
	Ship *_ship;
	bool powerEnable;
	float maxSpeed;
	bool invertVerticalAxis;
};

