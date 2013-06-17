#include "ShipHealthComponent.h"
#include "Ship.h"
#include "Stations\Station.h"
#include "Messages.h"
#include <stdlib.h>


ShipHealthComponent::ShipHealthComponent(Ship* ship) : HealthComponent()
{
	this->ship_ = ship;
	updateHealth();

	//listen to health changes
	Network::GetInstance()->AddListener(PacketType::CLIENT_HEALTH_CHANGED, this);
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
		updateHealthToServer(StationType::ST_POWER, ship_->GetStation(ST_POWER)->getHealth());
		break;
	case 1:
		ship_->GetStation(ST_HELM)->decreaseHealth(damage);
		updateHealthToServer(StationType::ST_HELM, ship_->GetStation(ST_HELM)->getHealth());
		break;
	case 2:
		ship_->GetStation(ST_WEAPON)->decreaseHealth(damage);
		updateHealthToServer(StationType::ST_WEAPON, ship_->GetStation(ST_WEAPON)->getHealth());
		break;
	case 3:
		ship_->GetStation(ST_POWER)->decreaseHealth(damage * 0.5);
		ship_->GetStation(ST_HELM)->decreaseHealth(damage * 0.5);
		updateHealthToServer(StationType::ST_POWER, ship_->GetStation(ST_POWER)->getHealth());
		updateHealthToServer(StationType::ST_HELM, ship_->GetStation(ST_HELM)->getHealth());
		break;
	case 4:
		ship_->GetStation(ST_POWER)->decreaseHealth(damage * 0.5);
		ship_->GetStation(ST_WEAPON)->decreaseHealth(damage * 0.5);
		updateHealthToServer(StationType::ST_POWER, ship_->GetStation(ST_POWER)->getHealth());
		updateHealthToServer(StationType::ST_WEAPON, ship_->GetStation(ST_WEAPON)->getHealth());
		break;
	case 5:
		ship_->GetStation(ST_HELM)->decreaseHealth(damage * 0.5);
		ship_->GetStation(ST_WEAPON)->decreaseHealth(damage * 0.5);
		updateHealthToServer(StationType::ST_HELM, ship_->GetStation(ST_HELM)->getHealth());
		updateHealthToServer(StationType::ST_WEAPON, ship_->GetStation(ST_WEAPON)->getHealth());
		break;
	}
	updateHealth();

	entity->handleMessage(MESSAGES::DAMAGE);
}

void ShipHealthComponent::updateHealthToServer(int stationType, int stationHealth)
{
	//Vec3 position, Vec3 orientation, Vec velocity Vec3 acceleration, Vec3 angularAcceleration, Vec3 angularVelocity
	NetworkPacket healthPacket = NetworkPacket(PacketType::CLIENT_HEALTH_CHANGED);
	healthPacket << ship_->getTeamId(); // ID of the ship
	healthPacket << stationType; // Which station is updated
	healthPacket << stationHealth; // send the health of that station along

	//send package
	Network::GetInstance()->SendPacket(healthPacket, false);
}


void ShipHealthComponent::HandleNetworkMessage(NetworkPacket packet)
{
	if(packet.GetType() == PacketType::CLIENT_HEALTH_CHANGED)
	{
		//Station and health
		int id;
		int stationType;
		int health;
		
		packet >> id;
		packet >> stationType;
		packet >> health;

		if(id == ship_->getTeamId())
		{
			//set the health for this stationtype
			ship_->GetStation((StationType)(stationType))->getHealthComponent()->setHealth(health);
		}
	}
}


ShipHealthComponent::~ShipHealthComponent(void)
{

}
