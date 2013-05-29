#ifndef WEAPON_STATION
#define WEAPON_STATION

#include "Station.h"

#include "../Ship.h"

class WeaponStation : public Station 
{
public:
	irr::core::vector3df rotationForeign;

	WeaponStation(Core*, Ship*);
	~WeaponStation();

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
	irr::core::vector3df rotationOwn;
};

#endif
