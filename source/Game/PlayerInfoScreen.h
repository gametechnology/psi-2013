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
	PlayerInfoScreen(irr::core::vector2df position, irr::core::vector2df size);
	~PlayerInfoScreen(void); 
	void update();
	void draw();
	void init();
	void setVisibility(bool visible);
	void setInfoText(const wchar_t* text);
	bool isVisible();
private:
	bool visible;
	const wchar_t* _teamInfoTxt;
	const wchar_t* playertext_team1;
	const wchar_t* playertext_team2;
	irr::core::vector2df _position;
	irr::core::vector2df _size;
	irr::gui::IGUIStaticText* stringObj;
	irr::gui::IGUIStaticText* playerGUIText;
};
#endif