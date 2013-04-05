#include "StateSwitchFighter.h"

StateSwitchFighter::StateSwitchFighter(StateSwitch::States startState, Enemy* parent)
{
	StateSwitchFighter::setState(startState);
	StateSwitchFighter::setParent(parent);
}

StateSwitchFighter::StateSwitchFighter(Enemy* parent)
{
	StateSwitchFighter::setState(StateSwitch::STATE_IDLE);
	StateSwitchFighter::setParent(parent);
}

StateSwitchFighter::~StateSwitchFighter()
{
	StateSwitch::~StateSwitch();
}

void StateSwitchFighter::handleIdle()
{
	StateSwitch::handleIdle();
}

void StateSwitchFighter::handleWander()
{
	StateSwitch::handleWander();
}

void StateSwitchFighter::handleFollow()
{
	StateSwitch::handleFollow();
}

void StateSwitchFighter::handleOffensive()
{
	StateSwitch::handleOffensive();
}

void StateSwitchFighter::handleDefensive()
{
	StateSwitch::handleDefensive();
}

void StateSwitchFighter::handleFleeing()
{
	StateSwitch::handleFleeing();
}