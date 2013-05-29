#ifndef HUDCOMPOSITE
#define HUDCOMPOSITE

#include <Engine/Composite.h>
#include <iostream>
#include <Irrlicht/irrlicht.h>

#include "HealthBar.h"
#include "BackButton.h"
#include "HudHelpText.h"

class HudComposite : public Composite
{
public:
	HudComposite(Core*, Interface*, int* health, int* power, irr::core::rect<irr::s32> buttonPos, std::string* helpText); //this change was necessary to get the game IGUIEnviroment
	~HudComposite(); 

	virtual void init();

	HealthBar* energyBar;
	HealthBar* healthBar;
	HudHelpText* hudHelpText;
	BackButton* backButton; //if I let it here is giving errors
	irr::gui::IGUIEnvironment* guiEnviroment;
private:
	Core* _core;
	Interface* _interface;
};

#endif

