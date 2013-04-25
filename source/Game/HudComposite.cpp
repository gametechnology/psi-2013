#include "HudComposite.h"


HudComposite::HudComposite(Composite* parent, int* health, int* energy) : Composite(parent)
{
	healthBar = new HealthBar(this, vector2df(50, 10), health, vector2df(20, 6), 6, SColor(255, 255, 100,100));
	energyBar = new HealthBar(this, vector2df(50, 60), energy, vector2df(20, 6), 6, SColor(255, 100, 100,255));
	//button
	//minimap
	//text
	addComponent(healthBar);
	addComponent(energyBar);
}


HudComposite::~HudComposite(void)
{
}
