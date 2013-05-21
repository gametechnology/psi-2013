#pragma once
#include "../Ship.h"

class HelmStation : public Station {
public:
	HelmStation(Ship *ship);
	~HelmStation();

	void onAdd();
	void init();

	void update();
	void draw();

	void enable();
	void disable();

	void OnEnabled(){};
	void OnDisabled(){};
	void DoCameraShake(){};
private:
	irr::video::ITexture *_stationTexture;
};
