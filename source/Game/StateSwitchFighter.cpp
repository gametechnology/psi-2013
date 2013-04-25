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

	if((*StateSwitchFighter::getParent()->inRangeList.getLast()->transform->position - *StateSwitchFighter::getParent()->transform->position).getLength() > 10)
	{
		StateSwitchFighter::getParent()->chase(*StateSwitchFighter::getParent()->inRangeList.getLast()->transform->position);
	}
}

void StateSwitchFighter::handleOffensive()
{
	StateSwitch::handleOffensive();
	if(!StateSwitchFighter::getParent()->inRangeList.empty())
	{
		if((*StateSwitchFighter::getParent()->inRangeList.getLast()->transform->position - *StateSwitchFighter::getParent()->transform->position).getLength() > 10)
		{
			StateSwitchFighter::getParent()->chase(*StateSwitchFighter::getParent()->inRangeList.getLast()->transform->position);
		}

		StateSwitchFighter::getParent()->setTarget(*StateSwitchFighter::getParent()->inRangeList.getLast()->transform->position);
	}

}

void StateSwitchFighter::handleDefensive()
{
	StateSwitch::handleDefensive();
}

void StateSwitchFighter::handleFleeing()
{
	StateSwitch::handleFleeing();
}