#include "DefenceStation.h"
#include "Station.h"
#include "..\Ship.h"

DefenceStation :: DefenceStation( Ship* ship) : Station( ship )
{
	this -> _stationType	= StationType::Defence;	
	std :: srand( time( NULL ) );
}

void DefenceStation :: DoCameraShake( )
{
	
}

void DefenceStation :: Damage( )
{
	//we damage a 'random' station.
	int random = rand( ) % 5;

	//Station *s = this -> _ship -> GetStation( ( STATION_TYPE ) random );
	_ship ->Blaat( );
	//std :: cout << &s;
}

int DefenceStation :: GetDamage( Station :: StationType )
{
	return 0;
}