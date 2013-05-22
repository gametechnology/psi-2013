#include "StateSwitchFighter.h"
#include <iostream>

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
	if(!StateSwitchFighter::getParent()->inRangeList.empty() && StateSwitchFighter::getParent()->inRangeList.back() != NULL)
		if((*StateSwitchFighter::getParent()->inRangeList.back()->transform->position - *StateSwitchFighter::getParent()->transform->position).getLength() > 10)
		{
			StateSwitchFighter::getParent()->chase(*StateSwitchFighter::getParent()->inRangeList.back()->transform->position);
		}
}

void StateSwitchFighter::handleOffensive()
{
	StateSwitch::handleOffensive();
	if(!StateSwitchFighter::getParent()->inRangeList.empty() && StateSwitchFighter::getParent()->inRangeList.back() != NULL)
	{
		if(StateSwitchFighter::getParent()->inRangeList.back()->transform->position == NULL)
		{
			StateSwitchFighter::getParent()->inRangeList.clear();
		}
			if((*StateSwitchFighter::getParent()->inRangeList.back()->transform->position - *StateSwitchFighter::getParent()->transform->position).getLength() > 10)
			{
				StateSwitchFighter::getParent()->chase(*StateSwitchFighter::getParent()->inRangeList.back()->transform->position);
			}
			StateSwitchFighter::getParent()->setTarget(*StateSwitchFighter::getParent()->inRangeList.back()->transform->position);
	}

}

void StateSwitchFighter::handleDefensive()
{
	StateSwitch::handleDefensive();
	if(!StateSwitchFighter::getParent()->inRangeList.empty() && StateSwitchFighter::getParent()->inRangeList.back() != NULL)
	{
		if((*StateSwitchFighter::getParent()->inRangeList.back()->transform->position - *StateSwitchFighter::getParent()->transform->position).getLength() > 20)
		{
			StateSwitchFighter::getParent()->chase(*StateSwitchFighter::getParent()->inRangeList.back()->transform->position);
		}
		StateSwitchFighter::getParent()->setTarget(*StateSwitchFighter::getParent()->inRangeList.back()->transform->position);
	}
}

void StateSwitchFighter::handleFleeing()
{
	StateSwitch::handleFleeing();
	if(!StateSwitchFighter::getParent()->inRangeList.empty() && StateSwitchFighter::getParent()->inRangeList.back() != NULL)
	{
		if((*StateSwitchFighter::getParent()->inRangeList.back()->transform->position - *StateSwitchFighter::getParent()->transform->position).getLength() > 20)
		{
			vector3df fleetarget = (*StateSwitchFighter::getParent()->inRangeList.back()->transform->position) + (*StateSwitchFighter::getParent()->transform->position);
			fleetarget = fleetarget.normalize()*50;
			StateSwitchFighter::getParent()->flee(fleetarget);
		}
	}
}