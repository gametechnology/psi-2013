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
	delete parent;
}

void StateSwitchFighter::setParent(Enemy* parent)
{
	StateSwitchFighter::parent = parent;
}

Enemy* StateSwitchFighter::getParent()
{
	return StateSwitchFighter::parent;
}