#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"

Station :: Station( Ship *ship, int startHealth ) : Component(ship)
{
	this ->	_ship	= ship;
	this -> _health = startHealth;
	//this -> _switchTime = 4.0f;
}

Station :: Station( Ship * ship ) : Component(ship)
{
	this -> _ship   = ship;
	this -> _health = 50;
	this -> _totalHealth = 50;
	this -> _tempTimer = 0;
	std::cout << "STARTTIMER: " << this->_tempTimer;
}

Station :: ~Station(void)
{
	//delete _ship;
	//delete _player;
	//delete _switchTime;
	//delete _playerOnStationTime;
	//delete _stunTime;
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

void Station::update()
{
	Component::update();
	updateHealth();
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

bool Station::getStationDestroyed( )
{
	return this -> _stationDestroyed;
}

void Station::setStationDestroyed(bool _destroyed)
{
	this -> _stationDestroyed = _destroyed;
}

void Station::updateHealth()
{
	this->_tempTimer++;
	if(this->_tempTimer >= 100)
	{
		if(rand()%10 > 5)
		{
			increaseHealth(10);
		}
		else
		{
			decreaseHealth(10);
		}
		this->_tempTimer=0;
	}
	std::cout << "TIMER: " << this->_tempTimer << " ";
}
int Station :: getHealth()
{
	return this -> _health;
}
void Station::decreaseHealth(int health)
{
	this->_health -= health;
	if(this->_health >= this->_totalHealth)
	{
		this->_health = this->_totalHealth;
	}
}
void Station::increaseHealth(int health)
{
	this->_health += health;
	if(this->_health <= 0)
	{
		this->_health = 0;
	}
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