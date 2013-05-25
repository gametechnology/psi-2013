#include "HealthComponent.h"
#include "../../include/Engine/Composite.h"
#include "Messages.h"


HealthComponent::HealthComponent(): Component()
{
	health = maxHealth;
}

//increase
void HealthComponent::increaseHealth(int health)
{
	(this->health + health) > maxHealth ? this->health = maxHealth : this->health + health;
}

//decrease
void HealthComponent::decreaseHealth(int health)
{
	(this->health - health) < 0 ? this->health = 0 : this->health - health;
}

//Handle messages
void HealthComponent::handleMessage(unsigned int message, void* data)
{
	//Power change
	if(message == Messages::HEALTH)
		health += *((int*)(data));
}

HealthComponent::~HealthComponent()
{
}