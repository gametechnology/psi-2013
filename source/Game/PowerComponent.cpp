#include "PowerComponent.h"
#include "../../include/Engine/Composite.h"
#include "Messages.h"

PowerComponent::PowerComponent(): Component()
{
	power = 0;
}

//increase power
void PowerComponent::increasePower(int power)
{
	(this->power + power) > maxPower ? this->power = maxPower : this->power + power;
}

//decrease power
void PowerComponent::decreasePower(int power)
{
	(this->power - power) < 0 ? this->power = 0 : this->power - power;
}

//handle messages
void PowerComponent::handleMessage(unsigned int message, void* data)
{
	//Power change
	if(message == Messages::POWER)
		power += *((int*)(data));
}

PowerComponent::~PowerComponent()
{
}