#include "PowerComponent.h"

PowerComponent::PowerComponent(): Component("PowerComponent")
{
	power = 0;
}

//increase power
void PowerComponent::increasePower(int power)
{
	this->power = (this->power + power) > maxPower ? maxPower : this->power + power;
}

//decrease power
void PowerComponent::decreasePower(int power)
{
	this->power = (this->power - power) < 0 ? 0 : this->power - power;
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