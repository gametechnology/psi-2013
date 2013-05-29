#ifndef DEFENCE_STATION
#define DEFENCE_STATION

#include "Station.h"

#include "../Ship.h"

#include <time.h>
#include <map>

class DefenceStation : public Station 
{
public:
	DefenceStation(Core* core, Ship* ship);
	~DefenceStation();
	
	void DoCameraShake();
	void Damage();
	int GetDamage(StationType stationType);

	Station *station;

	void enable();
	void disable();

	void OnEnabled();
	void OnDisabled();
};

#endif