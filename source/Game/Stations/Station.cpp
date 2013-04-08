#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"

Station :: Station( Ship *ship ) : Component(ship)
{
	this ->	_ship	= ship;

	//this -> _switchTime = 4.0f;
}

bool Station::HasPlayer()
{
	return ( this -> _player != NULL );
}

bool Station::SwitchTimePassed()
{
	return this -> _playerOnStationTime > this -> _switchTime;
}

STATION_TYPE Station :: GetStationType( )
{
	return this -> _stationType;
}

bool Station::IsStunned()
{
	time_t *t;
	time( t );

	//return true if the difference between the current time and the time the station was stunned is less than the defined stun time
	return difftime( *_stunTime, *t ) <= STUN_TIME;
}

void Station::Update(float time)
{
	//Update Stun Time
	//Update player on station time	
}

void Station :: OnDamage( )
{	
	//set the stun time to the current time (the time when it was stunned) 
	time( _stunTime );
}

bool Station::HasPower( )
{
	return true;//this->_ship->_powerStation->GetPower(this->_stationType) > 0;
}

bool Station::HasArmor( )
{
	return true;//this->_ship->_defenceStation->GetArmor(this->_stationType) > 0;
}

void Station :: Initialize( )
{
	this -> _player = NULL;
	this -> _playerOnStationTime = 0;
	this -> _stunTime = 0;
	this -> _switchTime = 0;

	if ( this -> _stationType != StationType ::  Power )	this -> _ship -> _powerStation		-> SubscribeStation( this );
	if ( this -> _stationType != StationType ::  Defence )	this -> _ship -> _defenceStation	-> SubscribeStation( this );
}