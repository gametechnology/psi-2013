#pragma once
#include "../Ship.h"
#include "../BasicShipMover.h"
#include "Engine\Network.h"
#include "Engine\NetworkPacket.h"

class HelmStation : public Station {
public:
	HelmStation(Ship *ship);
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
