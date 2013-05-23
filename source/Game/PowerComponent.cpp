#include "PowerComponent.h"
#include "../../include/Engine/Composite.h"


PowerComponent::PowerComponent(): Component()
{
	power = 0;
}

//increase

void PowerComponent::increasePower(int power)
{
	(this->power + power) > maxPower ? this->power = maxPower : this->power + power;
}

//end increase

//decrease

void PowerComponent::decreasePower(int power)
{
	(this->power - power) < 0 ? this->power = 0 : this->power - power;
}

//old decrease


PowerComponent::~PowerComponent()
{
}