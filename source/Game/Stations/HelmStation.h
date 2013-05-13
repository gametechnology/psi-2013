#ifndef HELM_STATION
#define HELM_STATION

#include "Station.h"
#include "..\Ship.h"
#include "Engine\Network.h"
#include "Engine\NetworkPacket.h"

class HelmStation : public Station 
{
public:
	HelmStation(Ship* ship);
	~HelmStation(void);	
	void DoCameraShake( );
	void OnEnabled();
	void update();
	void OnDisabled();
};

#endif