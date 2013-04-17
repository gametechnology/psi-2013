#include "Engine/Game.h"
#include "MainMenuScene.h"



MainMenuScene::MainMenuScene()
{
	//Get the device
	guiEnv = Game::guiEnv;

	///////////////////////////////////////////
	// MainMenu
	//////////////////////////////////////////
	//Creat the main menu window
	mainMenuWindow = guiEnv->addWindow(rect<s32>(position2di(80, 30),dimension2di(600, 550)),false,L"Main menu",0,100);

	//Add text and button
	createServerWindow_Button	= guiEnv->addButton(rect<s32>(position2di(50,105),dimension2di(200,25)),mainMenuWindow,MainMenuScene::CreateServerWindow, L"Create server",L"Go the Create server window.");
	joinServerWindow_Button		= guiEnv->addButton(rect<s32>(position2di(50,135),dimension2di(200,25)),mainMenuWindow,MainMenuScene::JoinServerWindow, L"Join Server",L"Go the Join server window.");
	Ipadresinput				= guiEnv->addEditBox(L"",rect<s32>(position2di(300,135),dimension2di(200,25)),true,mainMenuWindow);

	start_button					= guiEnv->addButton(rect<s32>(position2di(50,165),dimension2di(200,25)),mainMenuWindow,MainMenuScene::Quit, L"Start Game",L"Die in a fire.");
	start_button->setVisible(false);

	

	
	 // Store the appropriate data in a context structure.
    SAppContext context;
	context.device = Game::device;
    context.counter = 0;

	// Then create the event receiver, giving it that context structure.
	eventReceiver = new MainMenuEventReceiver(context);

    // And tell the device to use our custom event receiver.
	Game::input->setCustomEventReceiver(eventReceiver);
}

MainMenuScene::~MainMenuScene()
{
}
void MainMenuScene::StartGame()
{
	MapGenerator mapGen;
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->position.set(vector3df(100, 670, 0));
	SectorManager sectorManager(galaxyMap);
	sectorManager.init();
}



