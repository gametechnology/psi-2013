#include "Station.h"

using namespace irr;

Station::Station(Core* core, Interface* ui, Ship *ship, int startHealth) : Composite("Station")
{
	_core = core;
	_interface = ui;
	_ship = ship;

	_player = NULL;

	//Stations stats exist out of heath, power and shield
	_healthComponent = new HealthComponent();
	_powerComponent = new PowerComponent();
	_shieldComponent = new ShieldComponent();

	addComponent(_healthComponent);
	addComponent(_powerComponent);
	addComponent(_shieldComponent);

	//this -> _switchTime = 4.0f;
	helpTextString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fringilla consectetur mauris id rutrum. Vestibulum ante ipsum primis in faucibus.";
}

Station::Station(Core* core, Interface* ui, Ship * ship) : Composite("Station")
{
	_core = core;
	_interface = ui;
	_ship   = ship;

	_tempTimer = 0;
	_player = NULL;

	//Stations stats exist out of heath, power and shield
	_healthComponent = new HealthComponent();
	_powerComponent = new PowerComponent();
	_shieldComponent = new ShieldComponent();

	addComponent(_healthComponent);
	addComponent(_powerComponent);
	addComponent(_shieldComponent);

	helpTextString = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras fringilla consectetur mauris id rutrum. Vestibulum ante ipsum primis in faucibus.";
}

Station::~Station()
{
}

void Station::enable()
{
	Composite::setEnabled(true);
}

void Station::disable()
{
	Composite::setEnabled(false);
}

void Station::init() 
{
	Composite::init();

	driver = _core->getDriver();

	_playerOnStationTime = 0;
	_stunTime = 0;
	_switchTime = 0;
	_isOccupied = false;

	hud = new HudComposite(_core, _interface, &(_healthComponent->health), &(_powerComponent->power), irr::core::rect<irr::s32>(10,680,210,680 + 32), &helpTextString);
	addComponent(hud);
}

void Station::draw()
{
	Composite::draw();
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

bool Station::setPlayerOccupation(Player* player)
{
	if(_isOccupied)
		return false;

	_player = player;
	_player->setStation(_stationType);

	_isOccupied = true;	
	return true;
}

void Station::resetPlayerOccupation()
{
	_player->resetStation();
	_player = NULL;
	_isOccupied = false;
}

void Station::update()
{
	if(_player != NULL)
	{
		if(_player->getCurrentStation() == _stationType)
		{
			_isOccupied = false;
			_player = NULL;
		}
	}

	// Test code for testing energy of a station.
	if(_core->getInput()->isKeyboardButtonDown(KEY_ADD) && _powerComponent->power < 50)
		_powerComponent->power += 1;
	if(_core->getInput()->isKeyboardButtonDown(KEY_SUBTRACT) && _powerComponent->power > 0)
		_powerComponent->power -= 1;
	// End test code for testing energy of a station.

	updateHealth();

	if (_core->getInput()->isKeyboardButtonDown(KEY_ESCAPE)){
		// Load Shipmap
	}

	Composite::update();
}

void Station::handleMessage(unsigned int message,  void* data)
{
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
	NetworkPacket packet(CLIENT_LEAVE_STATION);
	packet << station;
	Network::GetInstance()->SendPacket(packet, true);
}