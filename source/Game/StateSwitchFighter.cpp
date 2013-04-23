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

	if((StateSwitchFighter::getParent()->inRangeList.getLast()->position - StateSwitchFighter::getParent()->position).getLength() > 10)
	{
		StateSwitchFighter::getParent()->chase(StateSwitchFighter::getParent()->inRangeList.getLast()->position);
	}
}

void StateSwitchFighter::handleOffensive()
{
	StateSwitch::handleOffensive();
	if(!StateSwitchFighter::getParent()->inRangeList.empty())
	{
		if((StateSwitchFighter::getParent()->inRangeList.getLast()->position - StateSwitchFighter::getParent()->position).getLength() > 10)
		{
			StateSwitchFighter::getParent()->chase(StateSwitchFighter::getParent()->inRangeList.getLast()->position);
		}
		StateSwitchFighter::getParent()->setTarget(StateSwitchFighter::getParent()->inRangeList.getLast()->position);
	}

}

void StateSwitchFighter::handleDefensive()
{
	StateSwitch::handleDefensive();
	if(!StateSwitchFighter::getParent()->inRangeList.empty())
	{
		if((StateSwitchFighter::getParent()->inRangeList.getLast()->position - StateSwitchFighter::getParent()->position).getLength() > 20)
		{
			StateSwitchFighter::getParent()->chase(StateSwitchFighter::getParent()->inRangeList.getLast()->position);
		}
		StateSwitchFighter::getParent()->setTarget(StateSwitchFighter::getParent()->inRangeList.getLast()->position);
	}
}

void StateSwitchFighter::handleFleeing()
{
	StateSwitch::handleFleeing();
	if(!StateSwitchFighter::getParent()->inRangeList.empty())
	{
		if((StateSwitchFighter::getParent()->inRangeList.getLast()->position - StateSwitchFighter::getParent()->position).getLength() > 20)
		{
			vector3df fleetarget = (StateSwitchFighter::getParent()->inRangeList.getLast()->position) + (StateSwitchFighter::getParent()->position);
			fleetarget = fleetarget.normalize()*50;
			StateSwitchFighter::getParent()->flee(fleetarget);
		}
	}
}