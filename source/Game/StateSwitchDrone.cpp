#include "StateSwitchDrone.h"
#include "RandomGenerator.h"

void StateSwitchDrone::handleIdle()
{
	StateSwitch::handleIdle();
}

void StateSwitchDrone::handleWander()
{
	StateSwitch::handleWander();
}

void StateSwitchDrone::handleFollow()
{
	StateSwitch::handleFollow();
	StateSwitchDrone::getParent()->chase(StateSwitchDrone::getParent()->inRangeList.getLast()->position);
}

void StateSwitchDrone::handleOffensive()
{
	StateSwitch::handleOffensive();
}

void StateSwitchDrone::handleDefensive()
{
	StateSwitch::handleDefensive();
}

void StateSwitchDrone::handleFleeing()
{
	StateSwitch::handleFleeing();
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