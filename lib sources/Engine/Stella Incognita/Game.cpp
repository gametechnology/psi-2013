#include <irrlicht.h>

#pragma comment(lib, "Irrlicht.lib")

// Disable DOS window.
#ifdef _IRR_WINDOWS_
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "Game.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;
//using namespace io;

// Predefine static variables
IrrlichtDevice* Game::device;
IVideoDriver* Game::driver;
stack<Scene*>* Game::scenes; 
Message* Game::messages;

Game::Game()
{
	//Create a new stack to store all scenes
	Game::scenes = new stack<Scene*>;
	
	// Create the irrlicht device 
	Game::device = createDevice(EDT_OPENGL, dimension2d<u32>(1280, 720), 16, false, false, false, 0);

	// If the device was not created correctly, then shut down the program
	if(Game::device) {
		// Create a driver 
		driver = Game::device->getVideoDriver();

		//Set title of the window
		Game::device->setWindowCaption(L"Stella Incognita");
	}
}

void Game::run()
{
		//Main loop
		while(Game::device->run())
		{
			//scenes->top()->Update();
			Game::driver->beginScene(true, true, SColor(255,100,101,140));
			Game::scenes->top()->smgr->drawAll();
			Game::driver->endScene();
		}

		Game::device->drop();
}

void Game::addScene(Scene* scene)
{
	Game::scenes->push(scene);
}

Game::~Game()
{
}
