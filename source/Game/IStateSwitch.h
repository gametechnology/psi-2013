#ifndef INTERFACE_STATESWITCH_H
#define INTERFACE_STATESWITCH_H

#include "Enemy.h"

class IStateSwitch
{
public:
	enum States {};

	void setState(States state);

	//handles the different states
	void update();

	Enemy* getParent();

private:

	States _currentState;
	States _newState;
	States _oldState;
};

#endif