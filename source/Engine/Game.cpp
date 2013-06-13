#include "Engine\Game.h"
#include "Engine\Hierarchy.h"
#include "../source/Game/NetworkInterface.h"

#pragma comment(lib, "Irrlicht.lib")

// Disable DOS window.
#ifndef _DEBUG
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

CollisionSystem* Game::collisionSystem;

Game::Game()
{
	//Create input manager
	input = new InputManager();

	// Create the irrlicht device 
	device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(1280, 720), 16, false, false, true, input);

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

	collisionSystem = new CollisionSystem();

	game->addComponent(sceneManager = new SceneManager());
}

void Game::init() {
	// Initialize the game entity
	game->init();
}

void Game::run()
{
	// Quick hack to switch to switch the order of draws. We had some problems with drawing stuff because of the draw order. 
	bool switchDraws = true;

	//Main loop
	while(device -> run( ) )
	{		
		input->endInputProcess();

		game->update();
		collisionSystem->update();

		// Clearing the screen
		driver -> beginScene(true, true, irr::video::SColor(255,100,101,140));

		//Irrlicht draw all
		sceneManager->drawAll();

		//Print the Hierarchy of the latest scene
		if (input->isKeyboardButtonReleased(KEY_KEY_V))
			Hierarchy::Visualize(sceneManager->getLastScene());

		// Quick hack to switch to switch the order of draws. We had some problems with drawing stuff because of the draw order.
		if(input->isKeyboardButtonPressed(KEY_KEY_K) && input->isKeyboardButtonPressed(KEY_KEY_J))
			switchDraws = !switchDraws;

		if(switchDraws)
		{
			//Irrlicht GUI
			guiEnv->drawAll();

			//Game engine draw
			game->draw();
		}
		else
		{
			//Game engine draw
			game->draw();

			//Irrlicht GUI
			guiEnv->drawAll();
		}

		// End the scene
		driver->endScene();

		// Other shit
		input->startInputProcess();
		Network::GetInstance()->DistributeReceivedPackets();
	}

	device->drop();
}

Game::~Game()
{

}