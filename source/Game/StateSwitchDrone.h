#ifndef STATE_SWITCH_DRONE_H
#define STATE_SWITCH_DRONE_H

#include "Engine\Game.h"
#include "Irrlicht\irrlicht.h"

#include "IStateSwitch.h"
#include "Enemy.h"

class StateSwitchDrone : public IStateSwitch
{

public:

	enum States
	{ 
		STATE_IDLE = 0,

		STATE_WANDER = 1,

		STATE_OFFENSIVE = 2,

		STATE_DEATH = 3
	};

	void setState(States state);

	void update();

	Enemy* getParent();

	void handleIdle();
	void handleWander();
	void handleOffensive();
	void handleDeath();

	StateSwitchDrone(States startState, Enemy* parent);

	StateSwitchDrone(Enemy* parent);

	~StateSwitchDrone();

private:

	States _currentState;
	States _newState;
	States _oldState;

	Enemy* _parent;
};

#endif