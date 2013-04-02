#include "StateSwitch.h"

void StateSwitch::updateState()
{
	if(newState_ != currentState_)
	{
		oldState_ = currentState_;
		currentState_ = newState_;
	}

	switch(currentState_)
	{
	case STATE_IDLE:
		handleIdle();
			break;
	case STATE_WANDER:
			handleWander();
			break;
	case STATE_FOLLOW:
			handleFollow();
			break;
	case STATE_OFFENSIVE:
			handleOffensive();
			break;
	case STATE_DEFENSIVE:
			handleDefensive();
			break;
	case STATE_FLEEING:
			handleFleeing();
			break;
	case STATE_DEATH:
			handleDeath();
			break;
	}
}

void StateSwitch::setState(States state)
{
	newState_ = state;
}

StateSwitch::States StateSwitch::getState()
{
	return currentState_;
}

void StateSwitch::handleIdle()
{

}

void StateSwitch::handleWander()
{

}

void StateSwitch::handleFollow()
{

}

void StateSwitch::handleOffensive()
{

}

void StateSwitch::handleDefensive()
{

}

void StateSwitch::handleFleeing()
{

}

void StateSwitch::handleDeath()
{
	delete this;
}

StateSwitch::~StateSwitch()
{
	currentState_.~States();
	newState_.~States();
	oldState_.~States();
}