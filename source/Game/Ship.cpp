#include "Ship.h"
#include "Stations/Station.h"

Ship::Ship( Composite * parent ) : Entity ( parent )
{
	//TODO remove temp stuff
	this -> _defenceStation		= new DefenceStation( this );
	this -> _helmStation		= new HelmStation( this );
	this -> _navigationStation	= new NavigationStation( this );
	this -> _weaponStation		= new WeaponStation( this );
	this -> _powerStation		= new PowerStation( this );

	this -> _defenceStation		-> Initialize();
	this -> _helmStation		-> Initialize();
	this -> _navigationStation	-> Initialize();
	this -> _weaponStation		-> Initialize();
	this -> _powerStation		-> Initialize();

	addComponent(_defenceStation);
	addComponent(_helmStation);
	addComponent(_navigationStation);
	addComponent(_weaponStation);
	addComponent(_powerStation);

	this -> updateShipHealth();
}

Ship::~Ship(void)
{

}

Station *Ship :: GetStation( STATION_TYPE s )
{
	this -> _defenceStation -> Damage( );

	switch( s )
	{
	case STATION_TYPE :: Defence:
		return this -> _defenceStation;
		break;
	case STATION_TYPE :: Helm:
		return this -> _helmStation;
		break;
	case STATION_TYPE :: Navigation:
		return this -> _navigationStation;
		break;
	//case STATION_TYPE :: Power:
	//	return this -> _powerStation;
	//	break;
	case STATION_TYPE :: Weapon:
		return this -> _weaponStation;
		break;
	};
	return NULL;
}

void Ship :: update()
{
	Entity :: update();

	this -> updateShipHealth();
}

void Ship :: updateShipHealth()
{
	this -> _shipHealth = 
		this -> _defenceStation -> getHealth() +
		this -> _helmStation -> getHealth() +
		this -> _navigationStation -> getHealth() +
		this -> _powerStation -> getHealth() +
		this -> _weaponStation -> getHealth();
}

int Ship :: getShipHealth()
{
	return this -> _shipHealth;
}
