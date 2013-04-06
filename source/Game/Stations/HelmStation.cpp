#include "Station.h"
#include "HelmStation.h"
//#include "Ship.h"

HelmStation :: HelmStation(Ship *ship) : Station( ship )
{
	//this->_stationType = StationType::Helm;
}

HelmStation :: ~HelmStation( )
{
	
}

void HelmStation :: DoCameraShake( )
{
	
}