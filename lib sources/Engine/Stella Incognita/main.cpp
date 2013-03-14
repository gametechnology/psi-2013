#include "Game.h"
#include "TestScene.h"
#include "Entity.h"

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

	// Create test scene
	TestScene* testScene = new TestScene();
	game.addScene(testScene);

	// Init the test scene
	testScene->Init();
	
	// Start the main loop
	game.run();

	// Debug for memory leaks
	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}