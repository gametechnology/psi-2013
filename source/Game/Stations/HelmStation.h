#ifndef HELM_STATION
#define HELM_STATION

#include "../Engine/Input.h"
#include "../Thruster.h"
#include "../Ship.h"
#include "Station.h"
#include "ShipMover.h"

class HelmStation : public Station 
{
private:

	Input* input;
	Camera* camera;
	Thruster* thrusters[3];

public:
	HelmStation(Ship* ship);
	~HelmStation(void);

	void DoCameraShake( );

	void init();
	void update();
};

#endif