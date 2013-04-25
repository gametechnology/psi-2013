#ifndef HUDCOMPOSITE
#define HUDCOMPOSITE

#include "Engine/Composite.h"
#include "../source/Game/HealthBar.h"
#include "../../include/Irrlicht/IGUIEnvironment.h"
#pragma once

class HudComposite : public Composite
{
public:
	HudComposite(Composite* parent, int* health, int* energy);
	~HudComposite(void);
	HealthBar* energyBar;
	HealthBar* healthBar;
	IGUIEnvironment* guiEnviroment;
	//diego's button
	//helptext
};

#endif

