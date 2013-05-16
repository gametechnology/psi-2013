#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"
#include "../StationStats.h"


Station :: Station( Ship *ship, int startHealth ) : Entity()
{
	this ->	_ship	= ship;

	//Add astationstats component to this station
	this->_stationStats = new StationStats();
	addComponent(_stationStats);
	
	//this -> _switchTime = 4.0f;
	helpTextString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fringilla consectetur mauris id rutrum. Vestibulum ante ipsum primis in faucibus.";

}

Station :: Station( Ship * ship ) : Entity()
{
	this -> _ship   = ship;
	this -> _tempTimer = 0;

	//Add astationstats component to this station
	this->_stationStats = new StationStats();
	addComponent(_stationStats);

	helpTextString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fringilla consectetur mauris id rutrum. Vestibulum ante ipsum primis in faucibus.";
	
}

void Station::onAdd()
{
	Entity::onAdd();

	// ?? This was also done in onAdd()
	// End energy testing variable for hud.
	//this->hud = new HudComposite(&_totalHealth, &energy, rect<s32>(10,680,210,680 + 32), &helpTextString);
	//this->addChild(hud);
	
}

void Station :: init() 
{
	Entity::init();

	driver = this->game->driver;

	this -> _player = NULL;
	this -> _playerOnStationTime = 0;
	this -> _stunTime = 0;
	this -> _switchTime = 0;

	// ?? This is also done in onAdd()
	//this->hud = new HudComposite(&(_stationStats->health), &(_stationStats->power), rect<s32>(10,680,210,680 + 32), &helpTextString);
	//this->addChild(hud);
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

StationType Station :: GetStationType( )
{
	return this -> _stationType;
}

bool Station::IsStunned()
{
	time_t *t = new time_t();
	time( t );

	//return true if the difference between the current time and the time the station was stunned is less than the defined stun time
	return difftime( *_stunTime, *t ) <= STUN_TIME;
}

void Station::update()
{
	Entity::update();
	// NOTE Component update goes automatic
	//Component::update();

	// Test code for testing energy of a station.
	if(game->input->isKeyboardButtonDown(KEY_ADD) && _stationStats->power < 50)
		_stationStats->power += 1;
	if(game->input->isKeyboardButtonDown(KEY_SUBTRACT) && _stationStats->power > 0)
		_stationStats->power -= 1;
	// End test code for testing energy of a station.

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
	return (_stationStats->power > 0);
}

bool Station::HasShield( )
{
	return (_stationStats->shield > 0);
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
	if(!this->getStationDestroyed())
	{
		this->_tempTimer++;
		if(this->_tempTimer >= 300)
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
	}
}

int Station :: getHealth()
{
	return (_stationStats->health > 0);
}

void Station::decreaseHealth(int health)
{
	_stationStats->health -= health;
	if(_stationStats->health <= 0)
	{
		setStationDestroyed(true);
	}
}

//The stations health is increased
void Station::increaseHealth(int health)
{
	_stationStats->health += health;
	if(_stationStats->health >=  StationStats::maxHealth)
	{
		_stationStats->health = StationStats::maxHealth;
	}
}

void Station::repairStation(int health)
{
	this->setStationDestroyed(false);
	_stationStats->health = health;
}