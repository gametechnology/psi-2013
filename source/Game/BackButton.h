#ifndef BACK_BUTTON_H
#define BACK_BUTTON_H

#include <Engine/Core.h>
#include <Engine/Component.h>
#include <Engine/Composite.h>
#include <Irrlicht/irrlicht.h>

class BackButton : public Component	
{
public:
	BackButton(Core*, irr::core::rect<irr::s32> position);
	~BackButton();

	bool isButtonPressed(); 
	void update();
	void draw();
	void init();
	bool visible;

private:
	Core* _core;

	irr::core::rect<irr::s32> position_;
	irr::core::rect<irr::s32> posRect;
	irr::video::ITexture* escButton;
	bool pressed;
	irr::gui::IGUIButton *button;
};
#endif
