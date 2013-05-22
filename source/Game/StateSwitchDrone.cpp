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
	if(!StateSwitchDrone::getParent()->inRangeList.empty() && StateSwitchDrone::getParent()->inRangeList.back() != NULL)
		StateSwitchDrone::getParent()->chase(*StateSwitchDrone::getParent()->inRangeList.back()->transform->position);
}

void StateSwitchDrone::handleOffensive()
{
	StateSwitch::handleOffensive();
	if(!StateSwitchDrone::getParent()->inRangeList.empty() && StateSwitchDrone::getParent()->inRangeList.back() != NULL)
		StateSwitchDrone::getParent()->chase(*StateSwitchDrone::getParent()->inRangeList.back()->transform->position);
}

void StateSwitchDrone::handleDefensive()
{
	StateSwitch::handleDefensive();
	if(!StateSwitchDrone::getParent()->inRangeList.empty() && StateSwitchDrone::getParent()->inRangeList.back() != NULL)
		StateSwitchDrone::getParent()->flee(*StateSwitchDrone::getParent()->inRangeList.back()->transform->position);
}

void StateSwitchDrone::handleFleeing()
{
	StateSwitch::handleFleeing();
}

StateSwitchDrone::StateSwitchDrone(StateSwitch::States startState, Enemy* parent)
{
	StateSwitchDrone::setState(startState);
	StateSwitchDrone::setParent(parent);
}

StateSwitchDrone::StateSwitchDrone(Enemy* parent)
{
	StateSwitchDrone::setState(StateSwitch::STATE_IDLE);
	StateSwitchDrone::setParent(parent);
}

StateSwitchDrone::~StateSwitchDrone()
{
	StateSwitch::~StateSwitch();
}