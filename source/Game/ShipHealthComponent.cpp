#include "ShipHealthComponent.h"
#include "Ship.h"
#include "Stations\Station.h"
#include <stdlib.h>


ShipHealthComponent::ShipHealthComponent(Ship* ship) : HealthComponent()
{
	this->ship_ = ship;
	updateHealth();
}
//this function gets the health from all the stations and sums it all up to get the health
void ShipHealthComponent::updateHealth(){
	health = 0;
	health += ship_->GetStation(ST_POWER)->getHealth();
	health += ship_->GetStation(ST_HELM)->getHealth();
	health += ship_->GetStation(ST_WEAPON)->getHealth();
	health /= 3;
}

//damage gets passed to the stations here. right now its random.
//but I suppose you can easily assign the damage to a specific station
void ShipHealthComponent::assignDamage(int damage){

	int a = rand() % 5;
	switch(a){
	case 0:
		ship_->GetStation(ST_POWER)->decreaseHealth(damage);
		break;
	case 1:
		ship_->GetStation(ST_HELM)->decreaseHealth(damage);
		break;
	case 2:
		ship_->GetStation(ST_WEAPON)->decreaseHealth(damage);
		break;
	case 3:
		ship_->GetStation(ST_POWER)->decreaseHealth(damage * 0.5);
		ship_->GetStation(ST_HELM)->decreaseHealth(damage * 0.5);
		break;
	case 4:
		ship_->GetStation(ST_POWER)->decreaseHealth(damage * 0.5);
		ship_->GetStation(ST_WEAPON)->decreaseHealth(damage * 0.5);
		break;
	case 5:
		ship_->GetStation(ST_HELM)->decreaseHealth(damage * 0.5);
		ship_->GetStation(ST_WEAPON)->decreaseHealth(damage * 0.5);
		break;
	}
	updateHealth();
}

ShipHealthComponent::~ShipHealthComponent(void)
{

}
