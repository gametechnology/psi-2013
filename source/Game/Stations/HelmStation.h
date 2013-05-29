#ifndef HELM_STATION
#define HELM_STATION

#include <Engine\Network.h>
#include <Engine\NetworkPacket.h>

#include "Station.h"

#include "../Ship.h"

#include "../BasicShipMover.h"

class HelmStation : public Station 
{
public:
	HelmStation(Core*, Interface*, Ship*);
	~HelmStation();
	void update();

	void onAdd();
	void init();
	void draw();

	void enable();
	void disable();

	void OnEnabled(){};
	void OnDisabled(){};
	void DoCameraShake(){};
private:
	irr::video::ITexture *_stationTexture;
};

#endif
