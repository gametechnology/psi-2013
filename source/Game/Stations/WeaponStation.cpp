#include "Station.h"
#include "WeaponStation.h"
#include "..\Ship.h"

WeaponStation::WeaponStation( Ship *ship ) : Station( ship )
{
	this -> _stationType = StationType::Weapon;
}

WeaponStation::~WeaponStation()
{

}

void WeaponStation :: DoCameraShake( )
{
	
}