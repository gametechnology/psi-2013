#include "HudComposite.h"


HudComposite::HudComposite( int* health, int* energy, rect<s32> buttonPos) : Entity()
{

	healthBar = new HealthBar( irr::core::vector2df(50, 110), health, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 255, 100,100));
	energyBar = new HealthBar( irr::core::vector2df(50, 160), energy, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 100, 100,255));
	backButton = new BackButton(buttonPos);
	std::cout << "hudcomposite parent type = " << typeid(hudHelpText).name();
	hudHelpText = new HudHelpText();
	//minimap
}

void HudComposite::onAdd() {

	addComponent(healthBar);
	addComponent(energyBar);
	addComponent(backButton);
	addComponent(hudHelpText);
	Entity::onAdd();
}


HudComposite::~HudComposite(void)
{
}
