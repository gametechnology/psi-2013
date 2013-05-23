#include "HudHelpText.h"

HudHelpText::HudHelpText(const wchar_t* helpText, irr::core::vector2df position, irr::core::vector2df size)
{
	visible = false;
	_helpTextStr = helpText;
	_position = position;
	_size = size;
}

HudHelpText::~HudHelpText(void)
{

}

void HudHelpText::init() {
	stringObj = getGame()->guiEnv->addStaticText(L"", irr::core::rect<irr::s32>(_position.X, _position.Y, _position.X + _size.X, _position.Y + _size.Y), false, true,(irr::gui::IGUIElement*)0, -1, true);
	stringObj->setOverrideColor(video::SColor(255, 0,0,0));
	stringObj->setBackgroundColor(video::SColor(200, 255, 255, 255));
}

void HudHelpText::update() {
	if (getGame()->input->isKeyboardButtonReleased(KEY_KEY_P)) {
		visible = !visible;
	}
}

void HudHelpText::draw() {
	if (!visible)  {
		stringObj->setText(L"Press 'P' to show help");
		stringObj->setMaxSize(irr::core::dimension2du(300, 40));
		return;
	}
	
	if (_helpTextStr != L"") {
		stringObj->setText(_helpTextStr);
		stringObj->setMaxSize(irr::core::dimension2du(_size.X, _size.Y));
	}
}

void HudHelpText::setVisibility(bool visible) {
	this->visible = visible;
}
bool HudHelpText::isVisible() {
	return this->visible;
}

void HudHelpText::setHelpText(const wchar_t* text) {
	_helpTextStr = text;
}