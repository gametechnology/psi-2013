#ifndef DEFENCE_STATION
#define DEFENCE_STATION

#include "Station.h"

#include "../Ship.h"

#include <time.h>
#include <map>

class DefenceStation : public Station 
{
public:
	DefenceStation(Core*, Interface*, Ship*);
	~DefenceStation();
	
	void DoCameraShake();
	void Damage();
	int GetDamage(StationType stationType);

	Station *station;

	virtual void enable();
	virtual void disable();
	virtual void update();
	virtual void init();
};

#endif