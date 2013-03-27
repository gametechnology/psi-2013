#include "Station.h"
#include "PowerStation.h"
#include "..\Ship.h"

PowerStation::PowerStation(Ship *ship) : Station( ship )
{
	Init( );
}

void PowerStation :: Init( )
{
	this -> _stationType		= StationType :: Power;
	this -> _stationsPowerUsage	= new map<STATION_TYPE, PowerUsage>( );

	//add all the stations to the dictionary
	for ( int i = 0; i < 5; i ++ )
		this -> _stationsPowerUsage	-> insert( ( STATION_TYPE ) i, PowerUsage( 10 ) );

	UpdateStationPower( STATION_TYPE :: Defence, 10 );
}

bool PowerStation :: IsPoolEmpty( )
{
	return this ->	_powerPool == 0;
}

void PowerStation :: UpdateStationPower( Station :: StationType stationType, int newValue )
{
	//we want a value that is equal to or larger than 0, but smaller than or equal to the total amount of power.
	int value = MIN_INT( MAX_INT( 0, newValue ), POWER_MAX );

	this -> _powerPool	= value;
	this -> _powerUsed	= POWER_MAX - this -> _powerPool;

	PowerUsage pu		= this -> _stationsPowerUsage -> find( stationType ) -> getKey( );
	pu.powerCurrent		= value;
}

void PowerStation :: DoCameraShake( )
{
	
}