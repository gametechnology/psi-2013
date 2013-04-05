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
	if(parent_->getHealth() <= 0)
	{
		StateSwitch::setState(StateSwitch::STATE_DEATH);
	}
	parent_->setVelocity(vector3df(0,0,0));

	if(parent_->arrayList.getSize() > 0)
	{
		int random = RandomGenerator::getRandomInt(10, 1);
		if(random > 5)
		{
			StateSwitch::setState(StateSwitch::STATE_FOLLOW);
		}else
		{
			StateSwitch::setState(StateSwitch::STATE_OFFENSIVE);
		}
	}
}

void StateSwitch::handleWander()
{
	if(parent_->getHealth() <= 0)
	{
		StateSwitch::setState(StateSwitch::STATE_DEATH);
	}
}

void StateSwitch::handleFollow()
{
	if(parent_->getHealth() <= 0)
	{
		StateSwitch::setState(StateSwitch::STATE_DEATH);
	}
}

void StateSwitch::handleOffensive()
{
	if(parent_->getHealth() <= 0)
	{
		StateSwitch::setState(StateSwitch::STATE_DEATH);
	}
}

void StateSwitch::handleDefensive()
{
	if(parent_->getHealth() <= 0)
	{
		StateSwitch::setState(StateSwitch::STATE_DEATH);
	}
}

void StateSwitch::handleFleeing()
{
	if(parent_->getHealth() <= 0)
	{
		StateSwitch::setState(StateSwitch::STATE_DEATH);
	}
}

void StateSwitch::handleDeath()
{
	delete parent_;
}

void StateSwitch::setParent(Enemy* parent)
{
	StateSwitch::parent_ = parent;
}

Enemy* StateSwitch::getParent()
{
	return StateSwitch::parent_;
}

StateSwitch::~StateSwitch()
{
	currentState_.~States();
	newState_.~States();
	oldState_.~States();
}