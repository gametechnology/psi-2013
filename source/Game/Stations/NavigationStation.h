#ifndef NAVIGATION_STATION
#define NAVIGATION_STATION

#include "Station.h"
#include "..\Ship.h"

class NavigationStation : public Station {
public:
	NavigationStation(Ship* ship);
	~NavigationStation(void);

	void DoCameraShake();
};

#endif