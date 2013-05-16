#ifndef HUDHELPTEXT
#define HUDHELPTEXT

#include <string>
#include <iostream>
#include "Irrlicht/Irrlicht.h"
#include "Engine/Component.h"
#include "Engine/Game.h"

class HudHelpText : public Component
{
public:
	HudHelpText(const wchar_t* helpText, irr::core::vector2df position);
	~HudHelpText(void); 
	void update();
	void draw();
	void init();
	void setVisibility(bool visible);
	bool isVisible();
private:
	bool visible;
	const wchar_t* _helpTextStr;
	irr::core::vector2df _position;
};
#endif

