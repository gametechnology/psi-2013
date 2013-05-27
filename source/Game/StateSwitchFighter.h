#ifndef STATE_SWITCH_FIGHTER_H
#define STATE_SWITCH_FIGHTER_H

#include "IStateSwitch.h"
#include "EnemyFighter.h"
#include "RandomGenerator.h"
#include <iostream>

class StateSwitchFighter : public IStateSwitch
{
public:

	enum States
	{ 
		STATE_IDLE = 0,

		STATE_WANDER = 1,

		STATE_FOLLOW = 2,

		STATE_OFFENSIVE = 3,

		STATE_DEFENSIVE = 4,

		STATE_FLEEING = 5,

		STATE_DEATH = 6
	};

	void setState(States state);

	void update();
	Enemy* getParent();

	void handleIdle();
	void handleWander();
	void handleFollow();
	void handleOffensive();
	void handleDefensive();
	void handleFleeing();
	void handleDeath();

	StateSwitchFighter(States startState, Enemy* parent);

	StateSwitchFighter(Enemy* parent);

	~StateSwitchFighter();

private:
	States _currentState;
	States _newState;
	States _oldState;

	Enemy* _parent;
	int _fireTimeCount;
	int _fireTime;
};

#endif