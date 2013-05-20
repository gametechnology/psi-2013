#include "HudHelpText.h"

HudHelpText::HudHelpText(const wchar_t* helpText, irr::core::vector2df position)
{
	visible = false;
	_helpTextStr = helpText;
	_position = position;
}

HudHelpText::~HudHelpText(void)
{

}

void HudHelpText::init() {
	stringObj = getGame()->guiEnv->addStaticText(L"Press F10 to show help", irr::core::rect<irr::s32>(_position.X, _position.Y, _position.X + 200, _position.Y + 100), false);
	stringObj->setOverrideColor(video::SColor(255, 255,0,135));
}

void HudHelpText::update() {
	if (getGame()->input->isKeyboardButtonReleased(KEY_F10)) { //TODO: Is called twice for no reason!!!
		visible = !visible;
		std::cout << "Toggle visible to " << visible << "\n";
	}
}

void HudHelpText::draw() {
	if (!visible)  {
		stringObj->setText(L"Press F10 to show help");
		return;
	}
	
	stringObj->setText(_helpTextStr);
	//todo: drawcode
}

void HudHelpText::setVisibility(bool visible) {
	this->visible = visible;
}
bool HudHelpText::isVisible() {
	return this->visible;
}