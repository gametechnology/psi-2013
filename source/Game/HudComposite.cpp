#include "HudComposite.h"
#include "Stations\Station.h"

using namespace irr;
using namespace irr::core;

HudComposite::HudComposite(Core* core, int* health, int* power, rect<s32> buttonPos, std::string* helpText) : Composite("HudComposite")
{
	_core = core;

	healthBar = new HealthBar(core, irr::core::vector2df(700, 80), health, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 255, 100,100));
	energyBar = new HealthBar(core, irr::core::vector2df(700, 130), power, irr::core::vector2df(20, 6), 5, irr::video::SColor(255, 100, 100,255));
	backButton = new BackButton(core, buttonPos);
	//hudHelpText = new HudHelpText(core, helpText, irr::core::rect<s32>(50, 500, 90, 520));
	
	onAdd();
}

void HudComposite::onAdd() {
	addComponent(healthBar);
	addComponent(energyBar);
	addComponent(backButton);
	//addComponent(hudHelpText);
}


HudComposite::~HudComposite(void)
{
}
