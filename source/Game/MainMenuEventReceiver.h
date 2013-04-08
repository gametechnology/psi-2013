#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"
#include "CIrrEventReceiver.h"

#ifndef MAINMENUEVENTRECEIVER
#define MAINMENUEVENTRECEIVER

// irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

// standard namespace
using namespace std;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

class MainMenuEventReveiver: public IEventReceiver
{
public:
	MainMenuEventReceiver(SAppContext & context) : Context(context) { }
	virtual void draw();
	~MainMenuEventReveiver();

	//Create the different windows
	IGUIWindow* mainMenuWindow;
	IGUIWindow* joinServerWindow;
	IGUIWindow* createServerWindow;
	
	//Create a gui environment
	IGUIEnvironment* guiEnv;
};

#endif

