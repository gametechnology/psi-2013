#ifndef HUDCOMPOSITE
#define HUDCOMPOSITE

#include "Engine/Entity.h"
#include "../source/Game/HealthBar.h"
#include"BackButton.h"
#include "../../include/Irrlicht/IGUIEnvironment.h"
#include "HudHelpText.h"
#pragma once


class HudComposite : public Entity
{
public:

	HudComposite( int* health, int* energy, irr::gui::IGUIEnvironment* env); //this change was necessary to get the game IGUIEnviroment
	~HudComposite(void);

	virtual void onAdd();

	HealthBar* energyBar;
	HealthBar* healthBar;
	HudHelpText* hudHelpText;
	BackButton* backButton; //if I let it here is giving errors
	irr::gui::IGUIEnvironment* guiEnviroment;
	 
	//helptext


	
};

#endif

