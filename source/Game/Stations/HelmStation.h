#ifndef HELM_STATION
#define HELM_STATION

#include "Station.h"
#include "..\Ship.h"
#include "Engine\Camera"

class HelmStation : public Station 
{
public:
	HelmStation(Ship* ship);
	~HelmStation(void);	
	void DoCameraShake( );
};

#endif