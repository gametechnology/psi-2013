#ifndef NAVIGATION_STATION
#define NAVIGATION_STATION

#include "Station.h"

#include "../Ship.h"

class NavigationStation : public Station
{
public:
	NavigationStation(Core*, Interface*, Ship*);
	~NavigationStation();

	void DoCameraShake();

	void enable();
	void disable();
private:
	CameraComponent* _navCamera;
};

#endif