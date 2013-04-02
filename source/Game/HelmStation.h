#pragma once
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"

class HelmStation : public Entity
{
public:
	HelmStation(Composite* parent);
	~HelmStation();

	void draw();
private:
	video::ITexture* _stationTexture;
};