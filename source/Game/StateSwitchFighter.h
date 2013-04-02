#ifndef STATE_SWITCH_FIGHTER_H
#define STATE_SWITCH_FIGHTER_H

#include "StateSwitch.h"

class StateSwitchFighter : public StateSwitch
{
public:
	virtual void handleIdle();

	virtual void handleWander();

	virtual void handleFollow();

	virtual void handleOffensive();

	virtual void handleDefensive();

	virtual void handleFleeing();

	virtual void handleDeath();

	StateSwitchFighter(StateSwitch::States startState);

	~StateSwitchFighter();

private:

};

#endif