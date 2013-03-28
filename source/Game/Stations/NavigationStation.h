#ifndef NAVIGATION_STATION
#define NAVIGATION_STATION
#pragma once

#include <iostream>
#include "Station.h"
#include "..\Ship.h"

class NavigationStation : public Station {
public:
	NavigationStation(Ship* ship);
	~NavigationStation(void);

	void DoCameraShake();
};

#endif