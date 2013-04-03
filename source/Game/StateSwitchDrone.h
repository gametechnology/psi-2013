#ifndef STATE_SWITCH_DRONE_H
#define STATE_SWITCH_DRONE_H

#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"

#include "StateSwitch.h"
#include "EnemyDrone.h"

class StateSwitchDrone : public StateSwitch
{

public:

	virtual void handleIdle();

	virtual void handleWander();

	virtual void handleFollow();

	virtual void handleOffensive();

	virtual void handleDefensive();

	virtual void handleFleeing();

	virtual void handleDeath();

	void setParent(EnemyDrone* parent);

	EnemyDrone* getParent();

	StateSwitchDrone(StateSwitch::States startState, EnemyDrone* parent);

	StateSwitchDrone(EnemyDrone* parent);

	~StateSwitchDrone();

private:

	EnemyDrone* parent;
};

#endif