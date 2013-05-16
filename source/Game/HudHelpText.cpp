#include "HudHelpText.h"

HudHelpText::HudHelpText(const wchar_t* helpText, irr::core::vector2df position)
{
	_helpTextStr = helpText;
	_position = position;
}

HudHelpText::~HudHelpText(void)
{

}

void HudHelpText::init() {
	
}

void HudHelpText::update() {
	if (getGame()->input->isKeyboardButtonReleased(KEY_F10)) {
		visible = !visible;
	}
}

void HudHelpText::draw() {
	if (!visible) return;

	irr::gui::IGUIStaticText* stringObj = getGame()->guiEnv->addStaticText(_helpTextStr, irr::core::rect<irr::s32>(_position.X, _position.Y, _position.X + 200, _position.Y + 100), false);
	stringObj->setOverrideColor(video::SColor(255, 255,0,135));
	//todo: drawcode

}

void HudHelpText::setVisibility(bool visible) {
	this->visible = visible;
}
bool HudHelpText::isVisible() {
	return this->visible;
}