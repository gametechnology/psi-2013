#include "Station.h"
#include "NavigationStation.h"
#include "..\Ship.h"

NavigationStation::NavigationStation(Ship *ship) : Station( ship )
{
	this->_stationType = StationType::Navigation;
	this -> setStationDestroyed(false);
}

NavigationStation :: ~NavigationStation()
{

}

void NavigationStation :: DoCameraShake( )
{
	
}