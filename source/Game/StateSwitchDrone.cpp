#include "StateSwitchDrone.h"

void StateSwitchDrone::handleIdle()
{

}

void StateSwitchDrone::handleWander()
{

}

void StateSwitchDrone::handleFollow()
{

}

void StateSwitchDrone::handleOffensive()
{

}

void StateSwitchDrone::handleDefensive()
{

}

void StateSwitchDrone::handleFleeing()
{

}

void StateSwitchDrone::handleDeath()
{

}

StateSwitchDrone::StateSwitchDrone(StateSwitch::States startState)
{
	StateSwitchDrone::setState(startState);
}

StateSwitchDrone::~StateSwitchDrone()
{
	StateSwitch::~StateSwitch();
}