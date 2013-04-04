#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "Ship.h"
#include "MapGenerator.h"

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
	//TODO remove temp stuff
	Ship ship = Ship(  );


	MapGenerator test;
	test.init(20,2,5);
	std::vector<float> chances;
	chances.push_back(25);
	chances.push_back(25);
	chances.push_back(25);
	chances.push_back(25);
	test.setBalanceChances(chances);
	GalaxyMap* map = test.createNewMap(300, 300, 15);

	// Create test scene
	Game::addScene(new HelmSceneTest());
	map->position.set(vector3df(10,50,0));
	Game::getCurrentScene()->addComponent(map);
	
	// Start the main loop
	Game::run();
	
	// Debug for memory leaks
	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}