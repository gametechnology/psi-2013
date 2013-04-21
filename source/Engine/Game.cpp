#include "Engine\Game.h"
#include "../source/Game/NetworkInterface.h"

#pragma comment(lib, "Irrlicht.lib")

// Disable DOS window.
#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

InputManager* Game::input;
Game::Game()
{
	//Create input manager
	Game::input = new InputManager();

	// Create the irrlicht device 
	Game::device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, true);

	// If the device was not created correctly, then shut down the program
	if(Game::device) {
		// Create a driver 
		driver = Game::device->getVideoDriver();

		//Get the GUI environment
		guiEnv = Game::device->getGUIEnvironment();

		//Set title of the window
		Game::device->setWindowCaption(L"Stella Incognita");
	}

	// Create the topmost node
	game = new Entity();
	game->addComponent(sceneManager = new SceneManager());

	// Then initialize it
	game->init();
}

void Game::run()
{
	//Main loop
	while(device -> run( ) )
	{		
		//Game :: getCurrentScene( ) -> update( );
		game->update();

		// Clearing the screen
		driver -> beginScene(true, true, irr::video::SColor(255,100,101,140));

		//Irrlicht draw all
		sceneManager->drawAll();

		//Game engine draw
		game->draw();

		//Irrlicht GUI
		guiEnv->drawAll();

		// End the scene
		driver->endScene();

		// Other shit
		Game::input->startInputProcess();
		Network::GetInstance()->DistributeReceivedPackets();
	}

	Game::device->drop();
}

Game::~Game()
{
	
}