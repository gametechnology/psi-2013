#include <Engine/Interface.h>

using namespace irr;
using namespace irr::core;
using namespace irr::gui;
using namespace irr::video;

Interface::Interface(IGUIEnvironment* gui, IVideoDriver* driver) : _guiEnv(gui), _driver(driver)
{
	for (u32 i=0; i<EGDC_COUNT ; ++i)
	{
		SColor col = _guiEnv->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(255);
		_guiEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}
}

Interface::~Interface()
{
	_guiEnv = NULL;	
}

void Interface::setFont(io::path fontPath)
{
	IGUIFont* font = _guiEnv->getFont(fontPath);
	_guiEnv->getSkin()->setFont(font);
	_guiEnv->getSkin()->setColor(EGDC_BUTTON_TEXT, SColor(255, 255, 255, 255));
}

void Interface::createButton(s32 x, s32 y, s32 width, s32 height, s32 id, IGUIElement* parent, const wchar_t* text)
{
	_interfaceElements.push_back(_guiEnv->addButton(rect<s32>(x, y, x+width, y+height), parent, id, text));
}

void Interface::addEditBox(s32 x, s32 y, s32 width, s32 height, s32 id, IGUIElement* parent, const wchar_t* text, bool border)
{
	_interfaceElements.push_back(_guiEnv->addEditBox(text, rect<s32>(x, y, x+width, y+height), border, parent, id));
}

void Interface::addListBox(s32 x, s32 y, s32 width, s32 height, s32 id, IGUIElement* parent, bool showBackground)
{
	_interfaceElements.push_back(_guiEnv->addListBox(rect<s32>(x, y, x+width, y+height), parent, id, showBackground));
}

void Interface::addStaticText(const wchar_t* text, s32 x, s32 y, s32 width, s32 height, s32 id, bool border, bool wordWrap, bool fillBackground, IGUIElement* parent)
{
	_interfaceElements.push_back(_guiEnv->addStaticText(text, rect<s32>(x, y, x+width, y+height), border, wordWrap, parent, id, fillBackground));
}

void Interface::addMessageBox(const wchar_t* caption, const wchar_t* message, bool blocking, s32 flags, IGUIElement* parent, io::path imagePath, s32 id)
{
	if(imagePath.size() > 0)
		_guiEnv->addMessageBox(caption, message, blocking, flags, parent, id, _driver->getTexture(imagePath));
	else
		_guiEnv->addMessageBox(caption, message, blocking, flags, parent, id);
}

void Interface::addImage(io::path path, int x, int y)
{
	_interfaceElements.push_back(_guiEnv->addImage(_driver->getTexture(path), position2d<int>(x, y)));
}

void Interface::resetInterface()
{
	std::list<IGUIElement*>::iterator iter;

	for(iter = _interfaceElements.begin(); iter != _interfaceElements.end(); iter++)
	{
		(*iter)->remove();
	}
	_interfaceElements.clear();
}

IGUIElement* Interface::getElementWithId(s32 id)
{
	std::list<IGUIElement*>::iterator iter;

	for(iter = _interfaceElements.begin(); iter != _interfaceElements.end(); iter++)
	{
		if((*iter)->getID() == id)
		{
			return *iter;
		}
	}

	return NULL;
}