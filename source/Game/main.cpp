#include "Engine/Game.h"
#include "HelmSceneTest.h"


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
	Game::addScene(new HelmSceneTest());
	
	// Start the main loop
	Game::run();

	// Debug for memory leaks5
	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}