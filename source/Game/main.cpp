#include <Engine/Game.h>
#include <Irrlicht/driverChoice.h>
#include "HelmSceneTest.h"
#include "EnemySceneTest.h"

#include "MainMenuScene.h"



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

int main()
{
	// Create engine
	Game game;

	// Create test scene
	//Game::addScene(new MainMenuScene());

	
	
	//Game::client->setupClient("145.92.13.97");
	//Need to create an Scene first or else it will crash, because I first delete then create scenes in SectorManager
	Game::addScene(new MainMenuScene());
	// Create sector manager that creates all the Scenes/Sectors
	

	// Start the main loop
	Game::run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}