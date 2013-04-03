#include "StateSwitchFighter.h"

StateSwitchFighter::StateSwitchFighter(StateSwitch::States startState, EnemyFighter* parent)
{
	StateSwitchFighter::setState(startState);
	StateSwitchFighter::setParent(parent);
}

StateSwitchFighter::StateSwitchFighter(EnemyFighter* parent)
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

}

void StateSwitchFighter::setParent(EnemyFighter* parent)
{
	StateSwitchFighter::parent = parent;
}

EnemyFighter* StateSwitchFighter::getParent()
{
	return StateSwitchFighter::parent;
}