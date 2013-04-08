#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "MainMenuScene.h"
#include "../../include/Irrlicht/irrlicht.h"
#include "../../include/Irrlicht/driverChoice.h"

// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

// Define some values that we'll use to identify individual GUI controls.
enum
{
    GUI_ID_QUIT_BUTTON = 101,
    GUI_ID_NEW_WINDOW_BUTTON,
    GUI_ID_FILE_OPEN_BUTTON,
    GUI_ID_TRANSPARENCY_SCROLL_BAR
};

class MyEventReceiver : public IEventReceiver
{
public:
    MyEventReceiver(SAppContext & context) : Context(context) { }

    virtual bool OnEvent(const SEvent& event)
    {
        if (event.EventType == EET_GUI_EVENT)
        {
            s32 id = event.GUIEvent.Caller->getID();
            IGUIEnvironment* env = Context.device->getGUIEnvironment();

            switch(event.GUIEvent.EventType)
            {   case EGET_SCROLL_BAR_CHANGED:
                if (id == GUI_ID_TRANSPARENCY_SCROLL_BAR)
                {
                    s32 pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
                    
                    for (u32 i=0; i<EGDC_COUNT ; ++i)
                    {
                        SColor col = env->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
                        col.setAlpha(pos);
                        env->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
                    }
                    
                }
                break;
				  case EGET_BUTTON_CLICKED:
                switch(id)
                {
                case GUI_ID_QUIT_BUTTON:
                    Context.device->closeDevice();
                    return true;

                case GUI_ID_NEW_WINDOW_BUTTON:
                    {
                    Context.listbox->addItem(L"Window created");
                    Context.counter += 30;
                    if (Context.counter > 200)
                        Context.counter = 0;

                    IGUIWindow* window = env->addWindow(
                        rect<s32>(100 + Context.counter, 100 + Context.counter, 300 + Context.counter, 200 + Context.counter),
                        false, // modal?
                        L"Test window");

                    env->addStaticText(L"Please close me",
                        rect<s32>(35,35,140,50),
                        true, // border?
                        false, // wordwrap?
                        window);
                    }
                    return true;

                case GUI_ID_FILE_OPEN_BUTTON:
                    Context.listbox->addItem(L"File open");
                    // There are some options for the file open dialog
                    // We set the title, make it a modal window, and make sure
                    // that the working directory is restored after the dialog
                    // is finished.
                    env->addFileOpenDialog(L"Please choose a file.", true, 0, -1, true);
                    return true;

                default:
                    return false;
                }
                break;

            case EGET_FILE_SELECTED:
                {
                    // show the model filename, selected in the file dialog
                    IGUIFileOpenDialog* dialog =
                        (IGUIFileOpenDialog*)event.GUIEvent.Caller;
                    Context.listbox->addItem(dialog->getFileName());
                }
                break;

            default:
                break;
            }
        }

        return false;
    }

private:
    SAppContext & Context;
};

int main()
{
	// Create engine
	Game game = Game();

	//Game::client->setupClient("145.92.13.97");

	// Create test scene
	Game::addScene(new HelmSceneTest());
	
	// Start the main loop
	Game::run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}