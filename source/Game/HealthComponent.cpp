#include "HealthComponent.h"
#include "../../include/Engine/Composite.h"


HealthComponent::HealthComponent(): Component()
{
	health = maxHealth;
}

//increase
void HealthComponent::increaseHealth(int health)
{
	(this->health + health) > maxHealth ? this->health = maxHealth : this->health + health;
}

//end increase

//decrease
void HealthComponent::decreaseHealth(int health)
{
	(this->health - health) < 0 ? this->health = 0 : this->health - health;
}

HealthComponent::~HealthComponent()
{
}