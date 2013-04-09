#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "MainMenuScene.h"
#include "../../include/Irrlicht/irrlicht.h"
#include "../../include/Irrlicht/driverChoice.h"

// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{
	// Create engine
	Game game;

	//Game::client->setupClient("145.92.13.97");

	// Create test scene
	//Game::addScene(new HelmSceneTest());
	Game::addScene(new MainMenuScene());
	
	// Start the main loop
	Game::run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}