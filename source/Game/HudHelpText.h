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
	HudHelpText(const wchar_t* helpText, irr::core::vector2df position, irr::core::vector2df size);
	~HudHelpText(void); 
	void update();
	void draw();
	void init();
	void setVisibility(bool visible);
	bool isVisible();
	void setHelpText(const wchar_t* text);
private:
	bool visible;
	const wchar_t* _helpTextStr;
	irr::core::vector2df _position;
	irr::core::vector2df _size;
	irr::gui::IGUIStaticText* stringObj;
};
#endif

