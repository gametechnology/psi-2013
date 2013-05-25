#ifndef NAVIGATION_STATION
#define NAVIGATION_STATION
#pragma once

#include "Station.h"
#include "..\Ship.h"

class NavigationStation : public Station {
public:
	NavigationStation(Ship* ship);
	~NavigationStation(void);

	void DoCameraShake();
	void enable();
	void OnEnabled();
	void OnDisabled();
};

#endif