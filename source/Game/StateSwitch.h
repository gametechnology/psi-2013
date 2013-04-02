#ifndef STATE_SWITCH_H
#define STATE_SWITCH_H

#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"

class StateSwitch
{
public:

	typedef enum {
		STATE_IDLE = 0,

		STATE_WANDER = 1,

		STATE_FOLLOW = 2,

		STATE_OFFENSIVE = 3,

		STATE_DEFENSIVE = 4,

		STATE_FLEEING = 5,

		STATE_DEATH = 6
	} States;

	void setState(States);

	States getState();

	void updateState();

	virtual void handleIdle();

	virtual void handleWander();

	virtual void handleFollow();

	virtual void handleOffensive();

	virtual void handleDefensive();

	virtual void handleFleeing();

	virtual void handleDeath();

	virtual ~StateSwitch();

private:

	States currentState_;
	States newState_;
	States oldState_;
};

#endif