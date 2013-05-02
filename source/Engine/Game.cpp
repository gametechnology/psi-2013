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
	//Create a new stack to store all scenes
	Game::scenes = new std::vector<Scene*>;

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
}

void Game::run()
{
	//Main loop
	while( Game :: device -> run( ) )
	{		
		game->update();

		// Clearing the screen
		Game :: driver -> beginScene(true, true, irr::video::SColor(255,100,101,140));

		//Irrlicht draw all
		//(*Game::scenes->begin())->sceneManager->drawAll();
		sceneManager->drawAll();

		//Game engine draw
		game->draw();

		//Irrlicht GUI
		Game::guiEnv->drawAll();

		// End the scene
		Game::driver->endScene();
		Game::input->startInputProcess();
		Network::GetInstance()->DistributeReceivedPackets();
	}

	Game::device->drop();
}

Scene* Game::getCurrentScene()
{
	return *scenes->end();
}

irr::scene::ISceneManager* Game::getSceneManager()
{
	return (*scenes->begin())->sceneManager;
}

void Game::addScene(Scene* scene)
{
	Game::scenes->push_back(scene);
	scene->init();
}

void Game::removeScene()
{
	Game::scenes->pop_back();
}

Game::~Game()
{
	//delete messages;
	//for (std::forward_list<Scene*>::iterator i = scenes->begin(); i != scenes->end(); ++i)
	//{
	//	delete (*i);
	//}

	delete scenes;
}