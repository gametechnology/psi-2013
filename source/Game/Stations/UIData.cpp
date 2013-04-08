#include "UIData.h"

UIData :: UIData( )
{
	this -> _stationsPowerUsage	= new map<Station :: StationType, PowerUsage>( );
	this -> powerPool	= POWER_MAX;
}

void UIData :: SubscribeStation( Station *s )
{
	this -> _stationsPowerUsage	-> insert( s -> GetStationType( ), PowerUsage( 0 ) );
}

void UIData :: UpdatePowerUsage( Station :: StationType s, int newValue )
{
	map<Station :: StationType, PowerUsage> :: Node *n = this -> _stationsPowerUsage -> find( s );

	int prevValue		= PowerUsage( n -> getValue( ) ).powerCurrent;
	powerPool			+= prevValue;

	//we want a value that is equal to or larger than 0, but smaller than or equal to the total amount of power.
	newValue			= MIN_INT( MAX_INT( 0, newValue ), powerPool );

	this -> powerPool	-= newValue;
	this -> _powerUsed	=  POWER_MAX - this -> powerPool;
	
	n -> setValue( newValue );
}

int UIData :: GetPower( Station :: StationType s )
{
	PowerUsage p = PowerUsage( this -> _stationsPowerUsage -> find( s ) -> getValue( ) );
	return p.powerCurrent;
}

UIData :: PowerUsage :: PowerUsage( int powerCurrent )
{
	this -> powerCurrent = powerCurrent;
}