#ifndef DEFENCE_STATION
#define DEFENCE_STATION

#include "Station.h"
#include "..\Ship.h"

class DefenceStation : public Station {

public:
	DefenceStation(Ship* ship);
	~DefenceStation(void);

	void DoCameraShake();
	int GetDamage(Station::StationType stationType) { return 0; }
	void Damage();
};

#endif