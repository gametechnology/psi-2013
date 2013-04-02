#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
	//Get the device
	guiEnv = Game::device->getGUIEnvironment();

	//set the first menu
	mainMenuState = MainMenuState::Main;

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
	createServerwindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Create a server",0,101);

	//Add text and buttons
	guiEnv->addStaticText(L"Create a server with the following IP address:", rect<s32>(position2di(50,50),dimension2di(200,20)), true, false, createServerwindow);
	fromCreateBackToMain_Button	= guiEnv->addButton(rect<s32>(position2di(300,105),dimension2di(200,25)),createServerwindow,MainMenuScene::CreateServer, L"Create server",L"Create the new server.");
	createServer_Button			= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),createServerwindow,MainMenuScene::fromCreateToMain, L"Back",L"Go back to the main menu");
	

	///////////////////////////////////////////
	// Join server window
	//////////////////////////////////////////
	joinServerWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Join a server",0,102);
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
		cout << "Create server has been pressed" << endl;

	if(rv.getEventCallerByID() == MainMenuScene::JoinServerWindow && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
		cout << "Join server has been pressed" << endl;

	if(rv.getEventCallerByID() == MainMenuScene::Quit && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
		cout << "Quit has been pressed" << endl;
			
	// start processing the events of keyboard/mouse button presses.
	rv.startEventProcess();
}


MainMenuScene::~MainMenuScene()
{
}
