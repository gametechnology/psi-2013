#include "Station.h"
#include "WeaponStation.h"
#include "..\Ship.h"

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