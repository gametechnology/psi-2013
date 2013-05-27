#ifndef BASIC_SHIP_MOVER
#define BASIC_SHIP_MOVER

#include "BasicMoverComponent.h"
#include "Ship.h"

/* 
* Basic ship mover, does not use thrusters.
*/

class BasicShipMover : public BasicMoverComponent
{
public:
	BasicShipMover(Ship* ship);
	~BasicShipMover();

	virtual void update();
	virtual void handleMessage(unsigned int message, void* data = 0){};
private:
	Ship *_ship;
};

#endif

