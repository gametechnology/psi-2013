#include "WeaponStation.h"

WeaponStation::WeaponStation( Ship *ship ) : Station( ship )
{
	this -> _stationType = ST_WEAPON;
	this -> setStationDestroyed(false);
}

WeaponStation::~WeaponStation()
{

}

void WeaponStation :: DoCameraShake( )
{
	
}

void WeaponStation :: OnEnabled(){

}

void WeaponStation :: OnDisabled(){

}