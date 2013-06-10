#include "StateSwitchDrone.h"
#include "RandomGenerator.h"
#include "Engine\IrrlichtNode.h"
#include <iostream>

void StateSwitchDrone::setState(States state)
{
	this->_currentState = state;
}

void StateSwitchDrone::update()
{
	//if(this->_newState != this->_currentState)
	//{
	//	this->_oldState = this->_currentState;
	//	this->_currentState = this->_newState;
	//}
	if(_currentState){
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
	_parent->setVelocity(vector3df(0,0,0));

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

	if(_parent->inRangeList.back() == NULL || _parent->inRangeList.back()->destroyed)
		return;

	if(!_parent->inRangeList.empty())
		_parent->chase(*_parent->inRangeList.back()->transform->position);
}

void StateSwitchDrone::handleDeath()
{
	_parent->destroyed = true;
	_parent->disable();
	for(unsigned i = 0; i < _parent->children.size(); i++)
	{
		if(dynamic_cast<IrrlichtNode*>(_parent->children[i]) != NULL)
		{
			_parent->children[i]->update();
		}
	}
}

StateSwitchDrone::StateSwitchDrone(States startState, Enemy* parent)
{
	StateSwitchDrone::setState(startState);
	this->_parent = parent;
}

StateSwitchDrone::StateSwitchDrone(Enemy* parent)
{
	StateSwitchDrone::setState(STATE_IDLE);
	this->_parent = parent;
}

StateSwitchDrone::~StateSwitchDrone()
{
}