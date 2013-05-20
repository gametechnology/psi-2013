#ifndef DEFENCE_STATION
#define DEFENCE_STATION

#include "Station.h"
#include <time.h>
#include <map>

class DefenceStation : public Station {
	
public:
	DefenceStation(Ship* ship);
	~DefenceStation();
	
	void DoCameraShake();
	void Damage();
	int GetDamage(StationType stationType);

	Station *station;

	void OnEnabled();
	void OnDisabled();
};

#endif