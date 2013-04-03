#ifndef STATE_SWITCH_FIGHTER_H
#define STATE_SWITCH_FIGHTER_H

#include "StateSwitch.h"
#include "EnemyFighter.h"

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

	void setParent(EnemyFighter* parent);

	EnemyFighter* getParent();

	StateSwitchFighter(StateSwitch::States startState, EnemyFighter* parent);

	StateSwitchFighter(EnemyFighter* parent);

	~StateSwitchFighter();

private:

	EnemyFighter* parent;
};

#endif