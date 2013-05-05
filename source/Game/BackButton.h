#ifndef BACK_BUTTON_H
#define BACK_BUTTON_H
#pragma once

#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Engine/Entity.h"
#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"


using namespace irr::core; 
using namespace irr::gui;

class BackButton :
	public Component
	
{
public:
	BackButton(irr::core::rect< s32 > position);
	~BackButton(void);

	bool isButtonPressed(); 
	void update();
	void draw();
	void init();
	bool visible;

private:
	irr::core::rect<s32> position_;
	rect<s32> posRect;
	irr::video::ITexture* escButton;
	bool pressed;
	IGUIButton *button;
};
#endif
