#include <Engine/Game.h>
#include <Irrlicht/driverChoice.h>
#include "HelmSceneTest.h"
#include "EnemySceneTest.h"

#include "MainMenuScene.h"

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
	//Game::addScene(new MainMenuScene());
	game->addScene(new MainMenuScene());

	//MapGenerator mapGen;
	//mapGen.init(20, 2, 5);
	//GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	//galaxyMap->position.set(vector3df(100, 670, 0));
	
	//Game::client->setupClient("145.92.13.97");
	//Need to create an Scene first or else it will crash, because I first delete then create scenes in SectorManager
	game->addScene(new MainMenuScene());
	// Create sector manager that creates all the Scenes/Sectors
	//SectorManager sectorManager(galaxyMap);
	//sectorManager.init();

	// Start the main loop
	game->run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}