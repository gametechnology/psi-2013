#include <Engine/Game.h>
#include <Irrlicht/driverChoice.h>

#include "HelmSceneTest.h"
#include "EnemySceneTest.h"
#include "MainMenuScene.h"
#include "GameScene.h"

#include "NetworkInterface.h"


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

	
	/////////////////////////////////////////
	//temporary until main menu works
	//Server 
	//Network::GetInstance()->InitializeServer(16);
	
	//Client 
	//Network::GetInstance()->InitializeClient("192.168.12.89");
	/////////////////////////////////////////

	// Create test scene
	Scene* scene = new GameScene();
	game->sceneManager->addScene("MainMenuScene", scene);

	//Game::client->setupClient("145.92.13.97");
	// Need to create an Scene first or else it will crash, because I first delete then create scenes in SectorManager
	// Create sector manager that creates all the Scenes/Sectors
	

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