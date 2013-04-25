#include "Station.h"
#include "NavigationStation.h"
#include "..\Ship.h"

NavigationStation::NavigationStation(Ship *ship) : Station( ship )
{
	this->_stationType = ST_NAVIGATION;
	this -> setStationDestroyed(false);
}

NavigationStation :: ~NavigationStation()
{

}

void NavigationStation :: DoCameraShake( )
{
	
}

void NavigationStation :: OnEnabled(){

}

void NavigationStation :: OnDisabled(){

}