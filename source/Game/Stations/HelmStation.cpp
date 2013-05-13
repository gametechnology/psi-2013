#include "HelmStation.h"

HelmStation :: HelmStation(Ship *ship) : Station( ship )
{
	this->stationType = ST_HELM;
	this -> setStationDestroyed(false);
}

HelmStation :: ~HelmStation( )
{
	
}

void HelmStation :: DoCameraShake( )
{
	
}

void HelmStation :: OnEnabled(){

}

void HelmStation ::OnDisabled(){
}