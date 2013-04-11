#include "DefenceStation.h"
#include "Station.h"
#include "..\Ship.h"

DefenceStation :: DefenceStation( Ship* ship) : Station( ship )
{
	this -> _stationType	= StationType::Defence;
	this -> _stations		= new map<STATION_TYPE, DefenceStation :: DefenceStats>( );
	this -> setStationDestroyed(false);
	std :: srand( time( NULL ) );
}

DefenceStation :: ~DefenceStation()
{
	
}

void DefenceStation :: DoCameraShake( )
{
	
}

void DefenceStation :: SubscribeStation( Station *s )
{
	this -> _stations -> insert( s -> GetStationType( ), DefenceStats( ) );
}

void DefenceStation :: Damage( )
{
	//we damage a 'random' station.
	int random = rand( ) % 5;

	//Station *s = this -> _ship -> GetStation( ( STATION_TYPE ) random );
	//std :: cout << &s;
}

int DefenceStation :: GetDamage( Station :: StationType )
{
	return 0;
}