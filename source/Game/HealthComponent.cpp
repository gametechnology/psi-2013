#include "HealthComponent.h"
#include "Messages.h"

HealthComponent::HealthComponent() : Component()
{
	maxHealth_ = 100;
	health_ = maxHealth_;
}

HealthComponent::HealthComponent(int maxHealth) : Component()
{
	maxHealth = abs(maxHealth);

	maxHealth_ = maxHealth;
	health_ = maxHealth_;
}

void HealthComponent::increaseHealth(int health)
{
	health = abs(health);
	health_ = (health_ + health) > maxHealth_ ? maxHealth_ : health_ + health;
}

void HealthComponent::decreaseHealth(int health)
{
	health = abs(health);
	health_ = (health_ - health) < 0 ? 0 : health_ - health;
}

void HealthComponent::setHealth(int health)
{
	if(health > maxHealth_)
		health_ = maxHealth_;
	else if(health < 0)
		health_ = 0;
	else
		health_ = health;
}

int HealthComponent::getHealth()
{
	return health_;
}

int* HealthComponent::getPointerToHealth()
{
	return &health_;
}

void HealthComponent::setMaxHealth(int maxHealth)
{
	maxHealth = abs(maxHealth);

	maxHealth_ = maxHealth;
	health_ = maxHealth_;
}

int HealthComponent::getMaxHealth()
{
	return maxHealth_;
}

void HealthComponent::handleMessage(unsigned int message, void* data)
{
	if(message == Messages::HEALTH)
	{
		int health = *((int*)(data));
		if(health < 0)
			decreaseHealth(health);
		else if(health > 0)
			increaseHealth(health);
	}
}

HealthComponent::~HealthComponent()
{
	Component::~Component();
}
