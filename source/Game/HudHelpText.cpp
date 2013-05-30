#include "HudHelpText.h"
#include <iostream>

using namespace irr;
using namespace irr::core;
using namespace irr::video;
using namespace irr::gui;
using namespace std;

HudHelpText::HudHelpText(Core* core, Interface* ui, const wchar_t* helpText, irr::core::vector2df position, irr::core::vector2df size) : Component("HudHelpText")
{
	_core = core;
	_interface = ui;

	visible = false;
	_helpTextStr = helpText;
	_position = position;
	_size = size;
}

HudHelpText::~HudHelpText()
{

}

void HudHelpText::init() 
{
	_interface->addStaticText(L"", _position.X, _position.Y, _size.X, _size.Y, 100, false, true, true, 0);
	stringObj = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(100));

	stringObj->setOverrideColor(SColor(255, 0,0,0));
	stringObj->setBackgroundColor(video::SColor(200, 255, 255, 255));
}

void HudHelpText::update() {
	if (_core->getInput()->isKeyboardButtonDown(KEY_KEY_P))
		visible = true;
	else
		visible = false;

	Component::update();
}

void HudHelpText::draw()
{
	if (!visible)  {
		stringObj->setText(L"Press 'P' to show help");
		stringObj->setMaxSize(dimension2du(300, 40));
		return;
	}
	else
	{
		stringObj->setText(_helpTextStr);
		stringObj->setMaxSize(dimension2du(_size.X, _size.Y));
	}
}

void HudHelpText::setVisibility(bool visible) {
	this->visible = visible;
}
bool HudHelpText::isVisible() {
	return visible;
}

void HudHelpText::setHelpText(const wchar_t* text) {
	_helpTextStr = text;
}