#ifndef PLAYERINFOSCREEN
#define PLAYERINFOSCREEN

#include <string>
#include <iostream>
#include "Irrlicht/Irrlicht.h"
#include "Engine/Component.h"
#include "Engine/Game.h"

class PlayerInfoScreen : public Component
{
public:
	PlayerInfoScreen(const wchar_t* helpText, irr::core::vector2df position, irr::core::vector2df size);
	~PlayerInfoScreen(void); 
	void update();
	void draw();
	void init();
	void setVisibility(bool visible);
	void setInfoText(const wchar_t* text);
	bool isVisible();
private:
	bool visible;
	const wchar_t* _helpTextStr;
	irr::core::vector2df _position;
	irr::core::vector2df _size;
	irr::gui::IGUIStaticText* stringObj;
};
#endif