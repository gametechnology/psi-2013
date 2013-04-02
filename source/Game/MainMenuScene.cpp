#include "MainMenuScene.h"


MainMenuScene::MainMenuScene()
{
	//Get the device
	guiEnv = Game::device->getGUIEnvironment();

	//set the first menu
	mainMenuState = MainMenuState::Main;

	//Createa a window
	window = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Menu",0,101);

	// add statictext above scrollbar.
	guiEnv->addStaticText(L"Transparent Control:", rect<s32>(position2di(50,50),dimension2di(200,20)), true, false, window);
	
	//Create the buttons
	createServerButton	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),window,MainMenuScene::CreateServer, L"Create server",L"Button 1");
	joinServerButton	= guiEnv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),window,MainMenuScene::JoinServer, L"Join Server",L"Button 2");
	quitButton			= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),MainMenuScene::window,Quit, L"Quit",L"Button 3");


}

void MainMenuScene::draw()
{
	// end process events
	rv.endEventProcess();
	
	//Draw all gui parts
	guiEnv->drawAll();
	
	// handling button pressed events:
	if(rv.getEventCallerByID() == MainMenuScene::CreateServer && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
		cout << "Create server has been pressed" << endl;

	if(rv.getEventCallerByID() == MainMenuScene::JoinServer && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
		cout << "Join server has been pressed" << endl;

	if(rv.getEventCallerByID() == MainMenuScene::Quit && rv.getEventCallerByElement(EGET_BUTTON_CLICKED))
		cout << "Quit 3 has been pressed" << endl;
			
	// start processing the events of keyboard/mouse button presses.
	rv.startEventProcess();
}


MainMenuScene::~MainMenuScene()
{
}
