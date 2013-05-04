#include "HudComposite.h"
#include <iostream>
BackButton* backButton; // I can not put this in the header file
HudComposite::HudComposite( int* health, int* energy, irr::gui::IGUIEnvironment* env) : Entity()
{
	HudComposite::guiEnviroment = env;

	healthBar = new HealthBar( irr::core::vector2df(50, 10), health, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 255, 100,100));
	energyBar = new HealthBar( irr::core::vector2df(50, 60), energy, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 100, 100,255));
	backButton = new BackButton(rect<s32>(10,240,110,240 + 32), guiEnviroment);
	//minimap
	//text

}

void HudComposite::onAdd() {

	addChild(healthBar);
	addChild(energyBar);
	addChild(backButton);

	Entity::onAdd();
}


HudComposite::~HudComposite(void)
{
}
