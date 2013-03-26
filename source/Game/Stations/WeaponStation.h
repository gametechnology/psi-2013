#ifndef WEAPON_STATION
#define WEAPON_STATION

#include "Station.h"
#include "..\Ship.h"

class WeaponStation : public Station {
public:
	WeaponStation( Ship *ship );
	~WeaponStation(void);

	void DoCameraShake();
};

#endif