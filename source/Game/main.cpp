#include <Engine/Game.h>
#include <Irrlicht/driverChoice.h>
#include "HelmSceneTest.h"
#include "EnemySceneTest.h"

#include "MainMenuScene.h"

#include "NetworkInterface.h"
#include "EmptyTestScene.h"


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

	//Add the MainMenu
	Game::addScene(new MainMenuScene());

	//Epic healthbar in an empty scene
	//Game::addScene(new EmptyTestScene());

	// Start the main loop
	Game::run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}