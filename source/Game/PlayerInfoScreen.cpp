#include "PlayerInfoScreen.h"

PlayerInfoScreen::PlayerInfoScreen(const wchar_t* helpText, irr::core::vector2df position, irr::core::vector2df size)
{
	visible = false;
	_helpTextStr = helpText;
	_position = position;
	_size = size;
}

PlayerInfoScreen::~PlayerInfoScreen(void)
{

}


void PlayerInfoScreen::init() {
	stringObj = getGame()->guiEnv->addStaticText(L"", irr::core::rect<irr::s32>(_position.X, _position.Y, _position.X + _size.X, _position.Y + _size.Y), false, true,(irr::gui::IGUIElement*)0, -1, true);
	stringObj->setOverrideColor(video::SColor(255, 0,0,0));
	stringObj->setBackgroundColor(video::SColor(200, 255, 255, 255));
}

void PlayerInfoScreen::update() {
	if (getGame()->input->isKeyboardButtonReleased(KEY_TAB)) {
		visible = !visible;
	}
}

void PlayerInfoScreen::draw() {
	if (!visible)  {
		stringObj->setText(L"");
		stringObj->setMaxSize(irr::core::dimension2du(1, 1));
		stringObj->setBackgroundColor(video::SColor(0, 255, 255, 255));
		return;
	}

	if (_helpTextStr != L"") {
		stringObj->setText(_helpTextStr);
		stringObj->setMaxSize(irr::core::dimension2du(_size.X, _size.Y));
		stringObj->setBackgroundColor(video::SColor(255, 255, 255, 255));
		stringObj->setDrawBorder(true);
		
	}
	

}

void PlayerInfoScreen::setVisibility(bool visible) {
	this->visible = visible;
}
bool PlayerInfoScreen::isVisible() {
	return this->visible;
}

void PlayerInfoScreen::setInfoText(const wchar_t* text) {
	_helpTextStr = text;
}
