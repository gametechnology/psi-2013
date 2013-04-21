#ifndef HELM_STATION
#define HELM_STATION

#include "Station.h"
#include "..\Ship.h"

class HelmStation : public Station 
{
public:
	HelmStation(Ship* ship);
	~HelmStation(void);	
	void DoCameraShake( );

	virtual void HandleNetworkMessage( NetworkPacket packet ); // implement the interface method
};

#endif