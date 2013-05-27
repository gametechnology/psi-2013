#ifndef PSI_GUI_BUILDER
#define PSI_GUI_BUILDER

#include <list>
#include <Irrlicht/irrlicht.h>

class Interface
{
public:
	Interface(irr::gui::IGUIEnvironment* gui, irr::video::IVideoDriver* driver);
	~Interface();

	void setFont(irr::io::path fontPath);

	void createButton(irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height, irr::s32 id, irr::gui::IGUIElement* parent, const wchar_t* text);
	void addEditBox(irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height, irr::s32 id, irr::gui::IGUIElement* parent, const wchar_t* text, bool border);
	void addListBox(irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height, irr::s32 id, irr::gui::IGUIElement* parent = 0, bool showBackground = false);

	void addStaticText(const wchar_t* text, irr::s32 x, irr::s32 y, irr::s32 width, irr::s32 height, irr::s32 id, bool border, bool wordWrap, bool fillBackground, irr::gui::IGUIElement* parent = 0);
	void addMessageBox(const wchar_t* caption, const wchar_t* message, bool blocking, irr::s32 flags, irr::gui::IGUIElement* parent, irr::io::path imagePath = "", irr::s32 id = 999);
	void addImage(irr::io::path, int x, int y);

	void resetInterface();

	irr::gui::IGUIElement* getElementWithId(irr::s32 id);
private:
	irr::gui::IGUIEnvironment* _guiEnv;
	irr::video::IVideoDriver* _driver;

	std::list<irr::gui::IGUIElement*> _interfaceElements;
};

#endif