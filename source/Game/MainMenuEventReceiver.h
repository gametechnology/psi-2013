#include "Irrlicht\irrlicht.h"
#include "Engine\Game.h"
#include "Engine\Scene.h"


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
    Game*			game;
    s32             counter;
    IGUIListBox*    listbox;
};

class MainMenuEventReceiver : public IEventReceiver
{
public:
	MainMenuEventReceiver(SAppContext & context);
	
	//Create the different windows
	IGUIWindow* mainMenuWindow;
	IGUIWindow* joinServerWindow;
	IGUIWindow* createServerWindow;

    virtual bool OnEvent(const SEvent& event);
    
	
private:
    SAppContext & Context;
	Game* contextGame;
};

#endif

