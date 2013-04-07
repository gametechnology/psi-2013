#include "DefenceStation.h"
#include "Station.h"
#include "..\Ship.h"

DefenceStation :: DefenceStation( Ship* ship) : Station( ship )
{
	this -> _stationType	= StationType::Defence;
	this -> _stations		= new map<STATION_TYPE, Stats>( );

	Init( );	
}

void DefenceStation :: Init( )
{
	std :: srand( time( NULL ) );

	for ( int i = 0; i < 5; i ++ )
	{
		this -> _stations -> insert( ( STATION_TYPE ) i, Stats( ) );
	}
}

void DefenceStation :: DoCameraShake( )
{
	
}

void DefenceStation :: Damage( )
{
	//we damage a 'random' station.
	int random = rand( ) % 5;

	//Station *s = this -> _ship -> GetStation( ( STATION_TYPE ) random );
	//_ship ->Blaat( );
	//std :: cout << &s;
}

int DefenceStation :: GetDamage( Station :: StationType )
{
	return 0;
}