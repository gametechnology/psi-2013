#include "HelmStation.h"

HelmStation :: HelmStation(Ship *ship) : Station( ship )
{
	this->_stationType = StationType::Helm;
	this -> setStationDestroyed(false);
}

HelmStation :: ~HelmStation( )
{
	
}

void HelmStation :: DoCameraShake( )
{
	
}
