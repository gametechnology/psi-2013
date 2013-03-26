#include "Station.h"
#include "PowerStation.h"
#include "..\Ship.h"

PowerStation::PowerStation(Ship *ship) : Station( ship )
{
	//this->_stationType = StationType::Power;
}

void PowerStation :: DoCameraShake( )
{
	
}