#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"
#include "../HealthComponent.h"
#include "../PowerComponent.h"
#include "../ShieldComponent.h"
#include "../GameScene.h"
#include "../PlayerManager.h"

Station :: Station( Ship *ship, int startHealth ) : Entity()
{
	this ->	_ship	= ship;

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
}

void Station :: init() 
{
	Entity::init();

	driver = this->game->driver;

	this -> _player = NULL;
	this -> _playerOnStationTime = 0;
	this -> _stunTime = 0;
	this -> _switchTime = 0;
	_isOccupied = false;
	_player = NULL;

	this->hud = new HudComposite(_healthComponent->getPointerToHealth(), &(_powerComponent->power), rect<s32>(10,680,210,680 + 32), &helpTextString);
	this->addChild(hud);

	// This
	playerlist = std::list<Player*>();
}

Station :: ~Station(void)
{
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

bool Station::setStationOccupation()
{
	if(_isOccupied)
		return false;

	_isOccupied = true;
	return true;
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

void Station::resetStationOccupation()
{
	_isOccupied = false;
}


void Station::resetPlayerOccupation()
{
	_player->resetStation();
	_player = NULL;
	_isOccupied = false;
}

void Station::update()
{
	Entity::update();

	if(_player != NULL)
	{
		if(_player->getCurrentStation() == _stationType)
		{
			_isOccupied = false;
			_player = NULL;
		}
	}

	// Test code for testing energy of a station.
	if(game->input->isKeyboardButtonDown(KEY_ADD) && _powerComponent->power < 50)
		_powerComponent->power += 1;
	if(game->input->isKeyboardButtonDown(KEY_SUBTRACT) && _powerComponent->power > 0)
		_powerComponent->power -= 1;
	// End test code for testing energy of a station.

	updateHealth();

	if (game->input->isKeyboardButtonDown(KEY_ESCAPE)){
		// Load Shipmap
		leaveStation(this->GetStationType());
		cout << "Leave Station";
	}
}


void Station :: draw( )
{	

	Entity::draw();
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
	return _healthComponent->getHealth();
}

void Station::decreaseHealth(int health)
{
	_healthComponent->decreaseHealth(health);
	if(_healthComponent->getHealth() <= 0)
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

int Station::getPower()
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
	_healthComponent->setHealth(health);
}

void Station::leaveStation(StationType station)
{
	_ship->leaveStation(station);
}