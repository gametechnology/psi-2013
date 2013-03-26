#ifndef DEFENCE_STATION
#define DEFENCE_STATION
#pragma once

#include "Station.h"
#include "..\Ship.h"
#include <time.h>

class DefenceStation : public Station
{
private:
	
public:
	DefenceStation( Ship* ship);
	~DefenceStation(void);

	void DoCameraShake();
	int GetDamage( Station :: StationType stationType );
	void Damage();

	Station *station;
};

#endif