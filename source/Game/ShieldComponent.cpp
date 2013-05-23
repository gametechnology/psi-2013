#include "ShieldComponent.h"
#include "../../include/Engine/Composite.h"
#include "Messages.h"

ShieldComponent::ShieldComponent(): Component()
{
	shield = 0;
}

//increase
void ShieldComponent::increaseShield(int shield)
{
	(this->shield + shield) > maxShield ? this->shield = maxShield : this->shield + shield;
}

//decrease
void ShieldComponent::decreaseShield(int shield)
{
	(this->shield - shield) < 0 ? this->shield = 0 : this->shield - shield;
}

//Handle messages
void ShieldComponent::handleMessage(unsigned int message, void* data)
{
	//Power change
	if(message == Messages::SHIELD)
		shield += *((int*)(data));
}

ShieldComponent::~ShieldComponent()
{
}