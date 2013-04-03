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