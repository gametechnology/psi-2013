#include "Engine\Game.h"
#include "Engine\Hierarchy.h"
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
	device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, true, Game::input);

	// If the device was not created correctly, then shut down the program
	if(device != NULL) {
		// Create a driver 
		driver = device->getVideoDriver();

		//Get the GUI environment
		guiEnv = device->getGUIEnvironment();

		//Set title of the window
		device->setWindowCaption(L"Stella Incognita");
	}

	// Create the topmost node
	game = new Entity();
	game->game = this;
	game->addComponent(sceneManager = new SceneManager());
}

void Game::init() {
	// Initialize the game entity
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

		//Print the Hierarchy of the latest scene
		if (Game::input->isKeyboardButtonReleased(KEY_KEY_V))
			Hierarchy::Visualize(sceneManager->getLastScene());

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