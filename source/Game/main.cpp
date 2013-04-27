#include <Engine/Game.h>
#include <Irrlicht/driverChoice.h>

#include "HelmSceneTest.h"
#include "EnemySceneTest.h"
#include "MainMenuScene.h"
#include "GameScene.h"

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
	Game* game = new Game();

	//Add the MainMenu
	//Scene* scene = new EnemySceneTest();
	Scene* scene = new GameScene();
	game->sceneManager->addScene("MainMenuScene", scene);

	// Need to create an Scene first or else it will crash, because I first delete then create scenes in SectorManager	

	// Initialize game
	game->init();

	// Start the main loop
	game->run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}