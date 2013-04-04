#include "StateSwitchDrone.h"
#include "RandomGenerator.h"

void StateSwitchDrone::handleIdle()
{
	int stageSwitchWander;
	stageSwitchWander = RandomGenerator::getRandomInt(1000, 0);
	if(stageSwitchWander == StateSwitchDrone::randomInt)
	{
		StateSwitchDrone::randomInt = RandomGenerator::getRandomInt(1000, 0);
		StateSwitchDrone::setState(StateSwitch::STATE_WANDER);
	}
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

void StateSwitchDrone::setParent(Enemy* parent)
{
	StateSwitchDrone::parent = parent;
}

Enemy* StateSwitchDrone::getParent()
{
	return StateSwitchDrone::parent;
}

StateSwitchDrone::StateSwitchDrone(StateSwitch::States startState, Enemy* parent)
{
	StateSwitchDrone::setState(startState);
	StateSwitchDrone::setParent(parent);
	StateSwitchDrone::randomInt = RandomGenerator::getRandomInt(100000, 0);
}

StateSwitchDrone::StateSwitchDrone(Enemy* parent)
{
	StateSwitchDrone::setState(StateSwitch::STATE_IDLE);
	StateSwitchDrone::setParent(parent);
	StateSwitchDrone::randomInt = RandomGenerator::getRandomInt(100000, 0);
}

StateSwitchDrone::~StateSwitchDrone()
{
	StateSwitch::~StateSwitch();
}