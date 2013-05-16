#include "StationStats.h"
#include "../../include/Engine/Composite.h"


StationStats::StationStats(): Component()
{
	health = maxHealth;
	power = 0;
	shield = 0;
}

//increase
void StationStats::increaseHealth(int health)
{
	(this->health + health) > maxHealth ? this->health = maxHealth : this->health + health;
}

void StationStats::increasePower(int power)
{
	(this->power + power) > maxPower ? this->power = maxPower : this->power + power;
}


void StationStats::increaseShield(int shield)
{
	(this->shield + shield) > maxShield ? this->shield = maxShield : this->shield + shield;
}
//end increase

//decrease
void StationStats::decreaseHealth(int health)
{
	(this->health - health) < 0 ? this->health = 0 : this->health - health;
}

void StationStats::decreasePower(int power)
{
	(this->power - power) < 0 ? this->power = 0 : this->power - power;
}


void StationStats::decreaseShield(int shield)
{
	(this->shield - shield) < 0 ? this->shield = 0 : this->shield - shield;
}
//old decrease


StationStats::~StationStats()
{
}