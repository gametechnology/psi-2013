#ifndef HUDHELPTEXT
#define HUDHELPTEXT
#pragma once
#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Engine\Entity.h"
#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"

using namespace irr::core; 
using namespace irr::gui;

class HudHelpText : public Component
{
public:
	HudHelpText(std::string* helpText, irr::core::rect< s32 > position);
	~HudHelpText(void);
	bool isButtonPressed(); 
	void update();
	void draw();
	void init();
	bool visible;
private: 
	irr::core::rect<s32> position_;
	std::string* helpTextStr;
	irr::video::ITexture* escButton;
	bool pressed;
	IGUIButton *button;
	IGUIEnvironment* env;
};
#endif

