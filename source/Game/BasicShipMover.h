#ifndef BASIC_SHIP_MOVER
#define BASIC_SHIP_MOVER

#include <Engine/Core.h>
#include "BasicMoverComponent.h"

#include "Ship.h"

/* 
* Basic ship mover, does not use thrusters.
*/

class BasicShipMover : public BasicMoverComponent
{
public:
	BasicShipMover(Core*, Ship*);
	~BasicShipMover();

	virtual void update();
	virtual void handleMessage(unsigned int message, void* data = 0){};
private:
	Core* _core;
};

#endif

