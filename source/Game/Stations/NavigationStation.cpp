#include "Station.h"
#include "NavigationStation.h"
#include "..\Ship.h"

NavigationStation::NavigationStation(Ship *ship) : Station( ship )
{
	//this->_stationType = StationType::Navigation;
}

void NavigationStation :: DoCameraShake( )
{
	
}