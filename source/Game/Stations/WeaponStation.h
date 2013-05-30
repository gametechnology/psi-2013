#ifndef WEAPON_STATION
#define WEAPON_STATION

#include "Station.h"

#include "../Ship.h"

class WeaponStation : public Station 
{
public:
	irr::core::vector3df rotationForeign;

	WeaponStation(Core*, Interface*, Ship*);
	~WeaponStation();

	virtual void init();

	virtual void update();
	virtual void draw();

	virtual void enable();
	virtual void disable();

	void DoCameraShake(){};
private:
	irr::video::ITexture *_stationTexture;
	irr::core::vector3df rotationOwn;
};

#endif
