#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"
//#include "../StationStats.h"
#include "../HealthComponent.h"
#include "../PowerComponent.h"
#include "../ShieldComponent.h"


Station :: Station( Ship *ship, int startHealth ) : Entity()
{
	this ->	_ship	= ship;

	//Add astationstats component to this station
	//this->_stationStats = new StationStats();
	//addComponent(_stationStats);

	//Stations stats exist out of heath, power and shield
	this->_healthComponent = new HealthComponent();
	this->_powerComponent = new PowerComponent();
	this->_shieldComponent = new ShieldComponent();
	addComponent(_healthComponent);
	addComponent(_powerComponent);
	addComponent(_shieldComponent);
	
	//this -> _switchTime = 4.0f;
	helpTextString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fringilla consectetur mauris id rutrum. Vestibulum ante ipsum primis in faucibus.";
}

Station :: Station( Ship * ship ) : Entity()
{
	this -> _ship   = ship;
	this -> _tempTimer = 0;

	//OLD = Add astationstats component to this station
	//this->_stationStats = new StationStats();
	//addComponent(_stationStats);

	//Stations stats exist out of heath, power and shield
	this->_healthComponent = new HealthComponent();
	this->_powerComponent = new PowerComponent();
	this->_shieldComponent = new ShieldComponent();
	addComponent(_healthComponent);
	addComponent(_powerComponent);
	addComponent(_shieldComponent);

	helpTextString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fringilla consectetur mauris id rutrum. Vestibulum ante ipsum primis in faucibus.";
	
}

void Station::onAdd()
{
	Entity::onAdd();

	// ?? This was also done in init()
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
	if(game->input->isKeyboardButtonDown(KEY_ADD) && _powerComponent->power < 50)
		_powerComponent->power += 1;
	if(game->input->isKeyboardButtonDown(KEY_SUBTRACT) && _powerComponent->power > 0)
		_powerComponent->power -= 1;
	// End test code for testing energy of a station.

	updateHealth();
	//Update Stun Time
	//Update player on station time	

	if (game->input->isKeyboardButtonDown(KEY_ESCAPE)){
	// Load Shipmap
	}
}


void Station :: draw( )
{	
	
	Entity::draw();
}
void Station::handleMessage(unsigned int message)
{
	switch(message)
	{
	case 0:
		
		break;
	case 1:
		break;
	}

}

void Station :: OnDamage( )
{	
	//set the stun time to the current time (the time when it was stunned) 
	time( _stunTime );
}

bool Station::HasPower( )
{
	return (_powerComponent->power > 0);
}

bool Station::HasShield( )
{
	return (_shieldComponent->shield > 0);
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
		//Temporary timer to test health increase and decrease.
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
	return (_healthComponent->health > 0);
}

void Station::decreaseHealth(int health)
{
	_healthComponent->decreaseHealth(health);
	if(_healthComponent->health <= 0)
	{
		setStationDestroyed(true);
	}
}

//The stations health is increased
void Station::increaseHealth(int health)
{
	_healthComponent->increaseHealth(health);
}

void Station::updatePower(int power)
{
	_powerComponent->power = power;
}

int Station :: getPower()
{
	return _powerComponent->power;
}

void Station::decreasePower(int power)
{
	_powerComponent->decreasePower(power);
	
}

//The stations power is increased
void Station::increasePower(int power)
{
	_powerComponent->increasePower(power);
}


void Station::repairStation(int health)
{
	this->setStationDestroyed(false);
	_healthComponent->health = health;
}

void Station::leaveStation(StationType station)
{
	NetworkPacket packet(PacketType::CLIENT_LEAVE_STATION);
	packet << station;
	Network::GetInstance()->SendPacket(packet, true);
}