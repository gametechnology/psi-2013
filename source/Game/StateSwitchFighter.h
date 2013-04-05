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

	StateSwitchFighter(StateSwitch::States startState, Enemy* parent);

	StateSwitchFighter(Enemy* parent);

	~StateSwitchFighter();
};

#endif