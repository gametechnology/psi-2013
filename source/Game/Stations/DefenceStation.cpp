#include "Station.h"
#include "DefenceStation.h"
#include "..\Ship.h"

DefenceStation::DefenceStation(Ship* ship) : Station( ship )
{
	this->_stationType = StationType::Defence;
}

void DefenceStation :: DoCameraShake( )
{
	
}