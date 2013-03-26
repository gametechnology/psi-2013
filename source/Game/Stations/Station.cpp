#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"

Station :: Station( Ship *ship )
{
	//this->_ship = ship;
	this->_switchTime = 4.0f;
}

bool Station::HasPlayer()
{
	return ( this -> _player != NULL );
}

bool Station::SwitchTimePassed()
{
	return this -> _playerOnStationTime > this -> _switchTime;
}

bool Station::IsStunned()
{
	return this->_stunTimeLeft > 0;
}

void Station::Update(float time)
{
	//Update Stun Time
	this->_stunTimeLeft -= time;
	if (this->_stunTimeLeft <= 0)
		this->_stunTimeLeft = 0;

	//Update player on station time
	this->_playerOnStationTime += time;
}

bool Station::HasPower()
{
	return true;//this->_ship->_powerStation->GetPower(this->_stationType) > 0;
}

bool Station::HasArmor()
{
	return true;//this->_ship->_defenceStation->GetArmor(this->_stationType) > 0;
}