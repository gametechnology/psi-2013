#ifndef HUDCOMPOSITE
#define HUDCOMPOSITE

#include "Engine/Entity.h"
#include "../source/Game/HealthBar.h"
#include "../../include/Irrlicht/IGUIEnvironment.h"
#pragma once

class HudComposite : public Entity
{
public:
	int _health;
	int _energy;

	HudComposite( int* health, int* energy);
	~HudComposite(void);

	virtual void onAdd();

	HealthBar* energyBar;
	HealthBar* healthBar;
	irr::gui::IGUIEnvironment* guiEnviroment;
	//diego's button
	//helptext
};

#endif

