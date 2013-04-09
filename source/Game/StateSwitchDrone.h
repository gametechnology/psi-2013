#ifndef STATE_SWITCH_DRONE_H
#define STATE_SWITCH_DRONE_H

#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"

#include "StateSwitch.h"
#include "Enemy.h"

class StateSwitchDrone : public StateSwitch
{

public:

	virtual void handleIdle();

	virtual void handleWander();

	virtual void handleFollow();

	virtual void handleOffensive();

	virtual void handleDefensive();

	virtual void handleFleeing();

	StateSwitchDrone(StateSwitch::States startState, Enemy* parent);

	StateSwitchDrone(Enemy* parent);

	~StateSwitchDrone();

private:
	int randomInt;
	float randomFloat;
};

#endif