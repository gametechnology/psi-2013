#include "HudComposite.h"
#include "Stations\Station.h"

HudComposite::HudComposite( int* health, int* power, rect<s32> buttonPos, std::string* helpText) : Entity()
{
	
	healthBar = new HealthBar( irr::core::vector2df(50, 110), health, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 255, 100,100));
	energyBar = new HealthBar( irr::core::vector2df(50, 160), power, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 100, 100,255));
	backButton = new BackButton(buttonPos);
	//hudHelpText = new HudHelpText(helpText, irr::core::rect<s32>(50, 500, 90, 520));
	//minimap
}

void HudComposite::onAdd() {
	addComponent(healthBar);
	addComponent(energyBar);
	addComponent(backButton);
	//addComponent(hudHelpText);
	Entity::onAdd();
}


HudComposite::~HudComposite(void)
{
}
