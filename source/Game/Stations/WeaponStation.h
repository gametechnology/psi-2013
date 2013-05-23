#pragma once
#include "../Ship.h"

class WeaponStation : public Station {
public:
	WeaponStation(Ship *ship);
	~WeaponStation();

	void onAdd();
	void init();
	irr::core::vector3df rotationForeign;
	
	void update();
	void draw();

	void enable();
	void disable();

	void OnEnabled(){};
	void OnDisabled(){};
	void DoCameraShake(){};
private:
	
	irr::video::ITexture *_stationTexture;
	irr::core::vector3df rotationOwn;
	
};
