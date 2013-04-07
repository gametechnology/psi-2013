#include "Ship.h"
#include "Stations/Station.h"

Ship::Ship(Composite * parent)
{
	
}

Ship :: Ship( )
{
	//TODO remove temp stuff
	this -> _defenceStation		= new DefenceStation( this );
	//this -> _helmStation		= new HelmStation( this );
	this -> _navigationStation	= new NavigationStation( this );
	this -> _powerStation		= new PowerStation( this );
	this -> _weaponStation		= new WeaponStation( this );

#ifdef HELM_STATION
	this -> _defenceStation		-> Damage( );
#endif
}

Ship::~Ship(void)
{

}

void Ship :: Blaat( )
{
	this -> _helmStation -> SwitchTimePassed( );
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
	case STATION_TYPE :: Power:
		return this -> _powerStation;
		break;
	case STATION_TYPE :: Weapon:
		return this -> _weaponStation;
		break;
	};
	return NULL;
}
