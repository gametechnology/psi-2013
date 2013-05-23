#include "ShieldComponent.h"
#include "../../include/Engine/Composite.h"


ShieldComponent::ShieldComponent(): Component()
{
	shield = 0;
}

//increase

void ShieldComponent::increaseShield(int shield)
{
	(this->shield + shield) > maxShield ? this->shield = maxShield : this->shield + shield;
}
//end increase

//decrease

void ShieldComponent::decreaseShield(int shield)
{
	(this->shield - shield) < 0 ? this->shield = 0 : this->shield - shield;
}
//old decrease


ShieldComponent::~ShieldComponent()
{
}