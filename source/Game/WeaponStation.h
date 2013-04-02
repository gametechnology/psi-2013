#pragma once
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class WeaponStation : public Entity
{
public:
	WeaponStation(Composite* parent);
	~WeaponStation();

	void draw();
private:
	video::ITexture* _stationTexture;
};