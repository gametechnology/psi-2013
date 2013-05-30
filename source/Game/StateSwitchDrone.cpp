#include "StateSwitchDrone.h"

void StateSwitchDrone::setState(States state)
{
	this->_newState = state;
}

void StateSwitchDrone::update()
{
	if(this->_newState != this->_currentState)
	{
		this->_oldState = this->_currentState;
		this->_currentState = this->_newState;
	}

	switch(this->_currentState)
	{
	case STATE_IDLE:
			handleIdle();
			break;
	case STATE_WANDER:
			handleWander();
			break;
	case STATE_OFFENSIVE:
			handleOffensive();
			break;
	case STATE_DEATH:
			handleDeath();
			break;
	}
}

Enemy* StateSwitchDrone::getParent()
{
	return this->_parent;
}

void StateSwitchDrone::handleIdle()
{
	if(_parent->getHealth() <= 0)
	{
		setState(STATE_DEATH);
		return;
	}
	_parent->setVelocity(&irr::core::vector3df(0,0,0));

	if(_parent->inRangeList.size() > 0)
	{
		setState(STATE_OFFENSIVE);
	}
}

void StateSwitchDrone::handleWander()
{
	if(_parent->getHealth() <= 0)
	{
		setState(STATE_DEATH);
		std::cout << _parent->getHealth() << ", Enemy is dead \n";
		return;
	}
	_parent->wander();

	if(_parent->inRangeList.size() > 0)
	{
		setState(STATE_OFFENSIVE);
	}
}


void StateSwitchDrone::handleOffensive()
{
	if(_parent->getHealth() <= 0)
	{
		setState(STATE_DEATH);
		return;
	}
	if(_parent->inRangeList.size() <= 0)
	{
		setState(STATE_IDLE);
	}

	if(_parent->inRangeList.back() == NULL || _parent->inRangeList.back()->isEnabled())
		return;

	if(!_parent->inRangeList.empty())
		_parent->chase(*_parent->inRangeList.back()->getPosition());
}

void StateSwitchDrone::handleDeath()
{	
	_parent->setEnabled(true);
	delete _parent;
}

StateSwitchDrone::StateSwitchDrone(States startState, Enemy* parent)
{
	StateSwitchDrone::setState(startState);
	_parent = parent;
}

StateSwitchDrone::StateSwitchDrone(Enemy* parent)
{
	StateSwitchDrone::setState(STATE_IDLE);
	_parent = parent;
}

StateSwitchDrone::~StateSwitchDrone()
{
}