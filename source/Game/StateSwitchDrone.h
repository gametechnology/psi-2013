#ifndef STATE_SWITCH_DRONE_H
#define STATE_SWITCH_DRONE_H

#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"
#include "StateSwitch.h"

class StateSwitchDrone : public StateSwitch
{
private:

public:

	virtual void handleIdle();

	virtual void handleWander();

	virtual void handleFollow();

	virtual void handleOffensive();

	virtual void handleDefensive();

	virtual void handleFleeing();

	virtual void handleDeath();

	StateSwitchDrone(StateSwitch::States startState);

	~StateSwitchDrone();
};

#endif