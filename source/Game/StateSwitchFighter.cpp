#include "StateSwitchFighter.h"

StateSwitchFighter::StateSwitchFighter(StateSwitch::States startState)
{
	StateSwitchFighter::setState(startState);
}

StateSwitchFighter::~StateSwitchFighter()
{
	StateSwitch::~StateSwitch();
}

void StateSwitchFighter::handleIdle()
{

}

void StateSwitchFighter::handleWander()
{

}

void StateSwitchFighter::handleFollow()
{

}

void StateSwitchFighter::handleOffensive()
{

}

void StateSwitchFighter::handleDefensive()
{

}

void StateSwitchFighter::handleFleeing()
{

}

void StateSwitchFighter::handleDeath()
{

}