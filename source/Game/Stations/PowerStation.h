#ifndef POWER_STATION
#define POWER_STATION

#include "Station.h"
#include "..\Ship.h"

class PowerStation : public Station {
public:
	PowerStation(Ship* ship);
	~PowerStation(void);

	void DoCameraShake();
	int GetPower(Station::StationType stationType) { return 0; }
};

#endif