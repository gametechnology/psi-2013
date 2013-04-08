#include "MainMenuScene.h"

// irrlicht namespaces
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;
using namespace std;

// Declare a structure to hold some context for the event receiver so that it
// has it available inside its OnEvent() method.
struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

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
			IGUIEnvironment* env = Game::device->getGUIEnvironment();

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

MainMenuScene::MainMenuScene()
{
	//Get the device
	guiEnv = Game::device->getGUIEnvironment();


	mainMenuState = Main;
	///////////////////////////////////////////
	// MainMenu
	//////////////////////////////////////////
	//Creat the main menu window
	IGUIWindow* mainMenuWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Main menu",0,100);

	//Add text and button
	createServerWindow_Button	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),mainMenuWindow,MainMenuScene::CreateServerWindow, L"Create server",L"Go the Create server window.");
	joinServerWindow_Button		= guiEnv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),mainMenuWindow,MainMenuScene::JoinServerWindow, L"Join Server",L"Go the Join server window.");
	quit_Button					= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),mainMenuWindow,MainMenuScene::Quit, L"Quit",L"Die in a fire.");

	 // Store the appropriate data in a context structure.
    SAppContext context;
	context.device = Game::device;
    context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	MainMenuEventReceiver receiver(context);

    // And tell the device to use our custom event receiver.
    Game::device->setEventReceiver(&receiver);

	//temporary solution. Crashes the game on quiting
	updateLoop();
}

void MainMenuScene :: updateLoop( )
{
	while(Game::device->run() && Game::driver)
	 if (Game::device->isWindowActive())
	 {
		  Game::driver->beginScene(true, true, SColor(0,200,200,200));
		  guiEnv->drawAll();
		  Game::driver->endScene();	  
	 }
	 Game::device->drop();
}

void MainMenuScene::draw()
{
	//Draw all gui parts
	guiEnv->drawAll();
}

MainMenuScene::~MainMenuScene()
{
}




