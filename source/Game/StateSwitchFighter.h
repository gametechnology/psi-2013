#ifndef STATE_SWITCH_FIGHTER_H
#define STATE_SWITCH_FIGHTER_H

#include "StateSwitch.h"
#include "Enemy.h"

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

	void setParent(Enemy* parent);

	Enemy* getParent();

	StateSwitchFighter(StateSwitch::States startState, Enemy* parent);

	StateSwitchFighter(Enemy* parent);

	~StateSwitchFighter();

private:

	EnemyF* parent;
};

#endif