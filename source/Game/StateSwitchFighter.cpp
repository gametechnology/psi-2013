#include "StateSwitchFighter.h"
#include "EnemyFighter.h"
#include "RandomGenerator.h"
#include "Engine\IrrlichtNode.h"
#include <iostream>

StateSwitchFighter::StateSwitchFighter(States startState, Enemy* parent)
{
	setState(startState);
	this->_parent = parent;

	this->_fireTimeCount = 0;
	this->_fireTime = 400;
}

StateSwitchFighter::StateSwitchFighter(Enemy* parent)
{
	StateSwitchFighter::setState(STATE_IDLE);
	this->_parent = parent;

	this->_fireTimeCount = 0;
	this->_fireTime = 400;
}

StateSwitchFighter::~StateSwitchFighter() { }

void StateSwitchFighter::setState(States state)
{
	this->_newState = state;
}

Enemy* StateSwitchFighter::getParent()
{
	return this->_parent;
}

void StateSwitchFighter::update()
{
	if(this->_newState != this->_currentState)
	{
		this->_oldState = this->_currentState;
		this->_currentState = this->_newState;
	}

	this->_fireTimeCount++;

	switch(this->_currentState)
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

void StateSwitchFighter::handleIdle()
{
	if(_parent->getHealth() <= 0)
	{
		setState(STATE_DEATH);
		return;
	}
	_parent->setVelocity(vector3df(0,0,0));

	if(_parent->inRangeList.size() > 0)
	{
		if(_parent->getHealth() <= (_parent->getMaxHealth() / 4))
		{
			setState(STATE_FLEEING);
		}else if(_parent->getHealth() <= (_parent->getMaxHealth() /2))
		{
			setState(STATE_DEFENSIVE);
		}else
		{
			int random = RandomGenerator::getRandomInt(10, 1);
			if(random > 5)
			{
				setState(STATE_FOLLOW);
			}else
			{
				setState(STATE_OFFENSIVE);
			}
		}
	}
}

void StateSwitchFighter::handleWander()
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
		if(_parent->getHealth() <= (_parent->getMaxHealth() / 4))
		{
			setState(STATE_FLEEING);
		}else if(_parent->getHealth() <= (_parent->getMaxHealth() /2))
		{
			setState(STATE_DEFENSIVE);
		}else
		{
			int random = RandomGenerator::getRandomInt(10, 1);
			if(random > 5)
			{
				setState(STATE_FOLLOW);
			}else
			{
				setState(STATE_OFFENSIVE);
			}
		}
	}
}

void StateSwitchFighter::handleFollow()
{
	if(_parent->inRangeList.size() <= 0)
	{
		setState(STATE_IDLE);
	}
	if(_parent->getHealth() <= 0)
	{
		setState(STATE_DEATH);
		return;
	}else if(_parent->getHealth() <= (_parent->getMaxHealth() /4))
	{
		setState(STATE_FLEEING);
	}else if(_parent->getHealth() <= (_parent->getMaxHealth() /2))
	{
		setState(STATE_DEFENSIVE);
	}else if(_parent->getHealth() < _parent->getMaxHealth())
	{
		setState(STATE_OFFENSIVE);
	}

	if(_parent->inRangeList.back() == NULL || _parent->inRangeList.back()->destroyed)
		return;

	if((*_parent->inRangeList.back()->transform->position - *_parent->transform->position).getLength() > 10)
	{
		_parent->chase(*_parent->inRangeList.back()->transform->position);
	}
}

void StateSwitchFighter::handleOffensive()
{
	if(_parent->getHealth() <= 0)
	{
		if(StateSwitchFighter::getParent()->inRangeList.back()->transform->position == NULL)
		{
			setState(STATE_DEATH);
			return;
		}
	}

	if(_parent->inRangeList.size() <= 0)
	{
		setState(STATE_IDLE);
	}else if(_parent->getHealth() <= (_parent->getMaxHealth() /4))
	{
		setState(STATE_FLEEING);
	}else if(_parent->getHealth() <= (_parent->getMaxHealth() /2))
	{
		setState(STATE_DEFENSIVE);
	}

	if(_parent->inRangeList.back() == NULL || _parent->inRangeList.back()->destroyed)
		return;

	if(!_parent->inRangeList.empty())
	{
		if((*_parent->inRangeList.back()->transform->position - *_parent->transform->position).getLength() > 10)
		{
			_parent->chase(*_parent->inRangeList.back()->transform->position);
		}
		_parent->setTarget(*_parent->inRangeList.back()->transform->position);
		if(this->_fireTimeCount >= this->_fireTime)
		{
			((EnemyFighter*)_parent)->fireLaserAt(_parent->getTarget());
			this->_fireTimeCount = 0;
		}
	}

}

void StateSwitchFighter::handleDefensive()
{
	if(_parent->getHealth() <= 0)
	{
		setState(STATE_DEATH);
		return;
	}

	if(_parent->inRangeList.size() <= 0)
	{
		setState(STATE_IDLE);
	}else if(_parent->getHealth() <= (_parent->getMaxHealth() /4))
	{
		setState(STATE_FLEEING);
	}

	if(_parent->inRangeList.back() == NULL || _parent->inRangeList.back()->destroyed)
		return;

	if(!_parent->inRangeList.empty())
	{
		if((*_parent->inRangeList.back()->transform->position - *_parent->transform->position).getLength() > 20)
		{
			_parent->chase(*_parent->inRangeList.back()->transform->position);
		}
		_parent->setTarget(*_parent->inRangeList.back()->transform->position);
		if(this->_fireTimeCount >= this->_fireTime)
		{
			((EnemyFighter*)_parent)->fireLaserAt(_parent->getTarget());
			this->_fireTimeCount = 0;
		}
	}
}

void StateSwitchFighter::handleFleeing()
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
	{
		if((*_parent->inRangeList.back()->transform->position - *_parent->transform->position).getLength() > 20)
		{
			vector3df fleetarget = (*_parent->inRangeList.back()->transform->position) + (*_parent->transform->position);
			fleetarget = fleetarget.normalize()*50;
			StateSwitchFighter::getParent()->flee(fleetarget);
		}
	}
}

void StateSwitchFighter::handleDeath()
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