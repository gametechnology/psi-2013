#ifndef HUDHELPTEXT
#define HUDHELPTEXT

#include <Irrlicht/Irrlicht.h>
#include <Engine/Component.h>
#include <Engine/Core.h>
#include <Engine/Interface.h>

class HudHelpText : public Component
{
public:
	HudHelpText(Core* core, Interface* _interface, const wchar_t* helpText, irr::core::vector2df position, irr::core::vector2df size);
	~HudHelpText();

	virtual void update();
	virtual void draw();
	virtual void init();

	void setVisibility(bool visible);
	bool isVisible();
	void setHelpText(const wchar_t* text);
private:
	Core* _core;
	Interface* _interface;
	bool visible;
	const wchar_t* _helpTextStr;
	irr::core::vector2df _position;
	irr::core::vector2df _size;
	irr::gui::IGUIStaticText* stringObj;
};
#endif

