#ifndef SHIPMOVER
#define SHIPMOVER

#include "BasicMoverComponent.h"
#include "Ship.h"
#include "Engine/InputManager.h"

class ShipMover : public BasicMoverComponent  {
public:
	ShipMover(Ship* parent);
	virtual ~ShipMover();
	virtual void update();
private:
	float maxFwdSpeed;
	float maxBwdSpeed;
};

#endif