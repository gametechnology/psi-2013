#include "Station.h"
#include "PowerStation.h"
#include "..\Ship.h"
#include <map>

PowerStation::PowerStation(Ship *ship) : Station( ship )
{
	this -> _stationType		= StationType :: Power;
	Init( );
}

void PowerStation :: Init( )
{
	this -> _stationsPowerUsage	= new map<STATION_TYPE, PowerUsage>( );
	Station :: Init( );
}

void PowerStation :: SubscribeStation( Station *s )
{
	this -> _stationsPowerUsage	-> insert( s -> GetStationType( ), PowerUsage( ) );
}

bool PowerStation :: IsPoolEmpty( )
{
	return this ->	_powerPool == 0;
}

void PowerStation :: UpdateStationPower( Station :: StationType stationType, int newValue )
{
	if ( stationType == STATION_TYPE :: Power )	return;	//we do nothing when the power station is selected.
	PowerUsage pu		= this -> _stationsPowerUsage -> find( stationType ) -> getKey( );

	int prevValue		= pu.powerCurrent;
	_powerPool			+= prevValue;

	//we want a value that is equal to or larger than 0, but smaller than or equal to the total amount of power.
	newValue			= MIN_INT( MAX_INT( 0, newValue ), _powerPool );

	this -> _powerPool	-= newValue;
	this -> _powerUsed	= POWER_MAX - this -> _powerPool;
	
	pu.powerCurrent		= newValue;
}

int PowerStation :: GetPower( Station::StationType stationType )
{
	PowerUsage p = this -> _stationsPowerUsage -> find( stationType ) -> getKey( );
	return p.powerCurrent;
}

void PowerStation :: DoCameraShake( )
{
	
}

PowerStation :: PowerUsage :: PowerUsage( int powerCurrent )
{
	this -> powerCurrent = powerCurrent;
};
