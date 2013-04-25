#include "HudComposite.h"


HudComposite::HudComposite( int* health, int* energy) : Entity()
{
	healthBar = new HealthBar( irr::core::vector2df(50, 10), health, irr::core::vector2df(20, 6), 6, irr::video::SColor(255, 255, 100,100));
	energyBar = new HealthBar( irr::core::vector2df(50, 60), energy, irr::core::vector2df(20, 6), 6, irr::video::SColor(255, 100, 100,255));
	//button
	//minimap
	//text
	addChild(healthBar);
	addChild(energyBar);
}


HudComposite::~HudComposite(void)
{
}
