#pragma once
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"
#include "WeaponCameraMover.h"
class WeaponStation : public Entity
{
public:
	WeaponStation(Composite* parent);
	~WeaponStation();
	WeaponCameraMover* cameramover;
	void draw();
private:
	video::ITexture* _stationTexture;
	
};