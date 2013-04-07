#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "MapGenerator.h"
#include "MainMenuScene.h"

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

	//Code to create the GalaxyMap
	/*MapGenerator mapGen;
	mapGen.init(20, 2, 5);
	GalaxyMap* galaxyMap = mapGen.createNewMap(300, 300, 15);
	galaxyMap->position.set(vector3df(100, 670, 0));*/

	//Game::client->setupClient("145.92.13.97");

	// Create test scene
	Game::addScene(new HelmSceneTest());

	//Code to add the GalaxyMap to the current scene
	//Game::getCurrentScene()->addComponent(galaxyMap);
	
	
	// Start the main loop
	Game::run();

	return 0;
}