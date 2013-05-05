#ifndef HUDHELPTEXT
#define HUDHELPTEXT
#pragma once
#include "Engine\Component.h"
#include "Engine\Composite.h"
#include "Engine/Entity.h"
#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"

class HudHelpText : public Component
{
public:
	HudHelpText();
	~HudHelpText(void);
private: 
	std::string* helpTextString;
};
#endif

