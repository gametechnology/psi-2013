#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "EnemySceneTest.h"
#include "MapGenerator.h"
#include "MainMenuScene.h"
#include "SectorManager.h"

// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main()
{
	// Create engine
	Game game = Game();

	//Game::client->setupClient("145.92.13.97");

	//Code to create the GalaxyMap
	/*MapGenerator mapGen;
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->position.set(vector3df(100, 670, 0));

	//Game::client->setupClient("145.92.13.97");
	//Need to create an Scene first or else it will crash, because I first delete then create scenes in SectorManager
	Game::addScene(new Scene());
	// Create sector manager that creates all the Scenes/Sectors
	SectorManager sectorManager(galaxyMap);
	sectorManager.init();*/

	// Create test scene
	Game::addScene(new HelmSceneTest());
	//change the scenes by commenting the other scenes and uncomment the one with the enemysceneTest for the enemies
	//Game::addScene(new EnemySceneTest());

	//Code to add the GalaxyMap to the current scene
	//Game::getCurrentScene()->addComponent(galaxyMap);
	
	
	// Start the main loop
	Game::run();

	return 0;
}