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

void StateSwitchDrone::setParent(EnemyDrone* parent)
{
	StateSwitchDrone::parent = parent;
}

EnemyDrone* StateSwitchDrone::getParent()
{
	return StateSwitchDrone::parent;
}

StateSwitchDrone::StateSwitchDrone(StateSwitch::States startState, EnemyDrone* parent)
{
	StateSwitchDrone::setState(startState);
	StateSwitchDrone::setParent(parent);
}

StateSwitchDrone::StateSwitchDrone(EnemyDrone* parent)
{
	StateSwitchDrone::setState(StateSwitch::STATE_IDLE);
	StateSwitchDrone::setParent(parent);
}

StateSwitchDrone::~StateSwitchDrone()
{
	StateSwitch::~StateSwitch();
}