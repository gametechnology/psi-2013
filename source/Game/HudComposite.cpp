#include "HudComposite.h"


HudComposite::HudComposite( int* health, int* energy) : Entity()
{
	_health = *health;
	_energy = *energy;
}

void HudComposite::onAdd() {
	healthBar = new HealthBar( irr::core::vector2df(50, 10), &_health, irr::core::vector2df(20, 6), 6, irr::video::SColor(255, 255, 100,100));
	energyBar = new HealthBar( irr::core::vector2df(50, 60), &_energy, irr::core::vector2df(20, 6), 6, irr::video::SColor(255, 100, 100,255));
	//button
	//minimap
	//text
	addChild(healthBar);
	addChild(energyBar);

	Entity::onAdd();
}


HudComposite::~HudComposite(void)
{
}
