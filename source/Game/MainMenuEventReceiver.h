#ifndef MAINMENUEVENTRECEIVER
#define MAINMENUEVENTRECEIVER

#include <Irrlicht\irrlicht.h>
#include <Engine/Core.h>
#include <Engine/Network.h>
#include <Engine/Interface.h>

#include "NetworkInterface.h"

enum InterfaceElement
{
	JOIN_GAME_BUTTON = 0,
	CREATE_GAME_BUTTON,
	START_GAME_BUTTON,
	QUIT_GAME_BUTTON,

	IP_INPUT_BOX,
	NAME_INPUT_BOX,
	PORT_INPUT_BOX,

	CLIENT_LIST
};

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
	Core* core;
	irr::s32 counter;
	Interface* u_interface;
};

class MainMenuEventReceiver : public IEventReceiver
{
public:
	MainMenuEventReceiver(SAppContext & context);

	virtual bool OnEvent(const SEvent& event);
private:
	SAppContext& context;
};

#endif

