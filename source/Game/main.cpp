#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "MapGenerator.h"

// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main()
{
	MapGenerator test;
	test.init(5,2,4);
	test.createNewMap();
	// Create engine
	Game game = Game();

	// Create test scene
	Game::addScene(new HelmSceneTest());
	
	// Start the main loop
	Game::run();
	
	// Debug for memory leaks
	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}