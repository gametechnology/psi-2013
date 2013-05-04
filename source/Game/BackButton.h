#ifndef BACK_BUTTON_H
#define BACK_BUTTON_H
#pragma once

#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Engine/Entity.h"
#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "HudComposite.h"


using namespace irr::core; 
using namespace irr::gui;

class BackButton :
	public Entity
	
{
public:
	BackButton(irr::core::rect< s32 > position, IGUIEnvironment* env);
	~BackButton(void);

	bool isButtonPressed(); 
	void update();
	void draw();
	void init();
	bool visible;

private:
	irr::core::vector2df position_;
	irr::video::ITexture* escButton;
	bool pressed;
	IGUIButton *button;
	IGUIEnvironment* env;
};
#endif
