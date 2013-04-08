#include "MainMenuScene.h"


// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};


// irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

class MainMenuEventReceiver : public IEventReceiver
{
public:
    MainMenuEventReceiver(SAppContext & context) : Context(context) { }
	
	//Create the different windows
	//IGUIWindow* mainMenuWindow;
	//IGUIWindow* joinServerWindow;
	//IGUIWindow* createServerWindow;

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType)
            { 
				 case EGET_BUTTON_CLICKED:
					switch(id)
					{
					case MainMenuScene::JoinServerWindow:
						 //joinServerWindow = env->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Join a server",0,102);
							//env->addButton(rect<s32>(position2di(300,105),dimension2di(200,25)),joinServerWindow,MainMenuScene::JoinServer, L"Join server",L"Join the server.");
							//env->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),joinServerWindow,MainMenuScene::fromJoinToMain, L"Back",L"Go back to the main menu");
						return true;
					case MainMenuScene::CreateServerWindow:
						//createServerWindow = env->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Create a server",0,101);
						//env->addStaticText(L"Create a server with the following IP address:", rect<s32>(position2di(50,50),dimension2di(200,20)), true, false, createServerWindow);
						//env->addButton(rect<s32>(position2di(300,105),dimension2di(200,25)),createServerWindow,MainMenuScene::CreateServer, L"Create server",L"Create the new server.");
						//env->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),createServerWindow,MainMenuScene::fromCreateToMain, L"Back",L"Go back to the main menu");
						return true;
					default:
						return false;
					}
                break;
            }
        }

        return false;
    }

private:
    SAppContext & Context;
};
