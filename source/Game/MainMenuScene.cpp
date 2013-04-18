#include "MainMenuScene.h"
#include "Irrlicht\irrlicht.h"

struct SAppContext
{
    IrrlichtDevice *device;
    s32             counter;
    IGUIListBox*    listbox;
};

MainMenuScene::MainMenuScene()
{
	//Get the device
	guiEnv = Game::device->getGUIEnvironment();

	//set the first menu
	mainMenuState = Main;

	///////////////////////////////////////////
	// MainMenu
	//////////////////////////////////////////
	//Creat the main menu window
	mainMenuWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Main menu",0,100);

	//Add text and button
	guiEnv->addStaticText(L"Main menu:", rect<s32>(position2di(50,50),dimension2di(200,20)), true, false, mainMenuWindow);
	createServerWindow_Button	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),mainMenuWindow,MainMenuScene::CreateServerWindow, L"Create server",L"Go the Create server window.");
	joinServerWindow_Button		= guiEnv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),mainMenuWindow,MainMenuScene::JoinServerWindow, L"Join Server",L"Go the Join server window.");
	quit_Button					= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),mainMenuWindow,MainMenuScene::Quit, L"Quit",L"Die in a fire.");

	///////////////////////////////////////////
	// Create server - window
	/////////////////////////////////////////
	createServerWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Create a server",0,101);
	createServerWindow->setVisible(false);
	//Add text and buttons
	guiEnv->addStaticText(L"Create a server with the following IP address:", rect<s32>(position2di(50,50),dimension2di(200,20)), true, false, createServerWindow);
	fromCreateBackToMain_Button	= guiEnv->addButton(rect<s32>(position2di(300,105),dimension2di(200,25)),createServerWindow,MainMenuScene::CreateServer, L"Create server",L"Create the new server.");
	createServer_Button			= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),createServerWindow,MainMenuScene::fromCreateToMain, L"Back",L"Go back to the main menu");
	

	///////////////////////////////////////////
	// Join server window
	//////////////////////////////////////////
	joinServerWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Join a server",0,102);
	joinServerWindow->setVisible(false);
	
	joinServer_Button			= guiEnv->addButton(rect<s32>(position2di(300,105),dimension2di(200,25)),joinServerWindow,MainMenuScene::JoinServer, L"Join server",L"Join the server.");
	fromJoinBackToMain_Button	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),joinServerWindow,MainMenuScene::fromJoinToMain, L"Back",L"Go back to the main menu");
}

void MainMenuScene::draw()
{
	// end process events
	rv.endEventProcess();
	
	//Draw all gui parts
	guiEnv->drawAll();
	
	// handling button pressed events:
	if(rv.getEventCallerByID() == MainMenuScene::CreateServerWindow && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
	{
		mainMenuWindow->setVisible(false);
		createServerWindow->setVisible(true);
	}

	if(rv.getEventCallerByID() == MainMenuScene::JoinServerWindow && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
	{
		mainMenuWindow->setVisible(false);
		joinServerWindow->setVisible(true);
	}


	if(rv.getEventCallerByID() == MainMenuScene::Quit && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
		cout << "Quit has been pressed" << endl;
			
	// start processing the events of keyboard/mouse button presses.
	rv.startEventProcess();
}


MainMenuScene::~MainMenuScene()
{
}

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
			{
			//TODO: cases when a button is pressed
			default:
				break;
			}
		}
		return false;
	}
private:
	SAppContext &Context;
};