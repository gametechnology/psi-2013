#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "WeaponScene.h"

bool Isweapon = true;

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
	if(!Isweapon){
		// Create test scene
		Game::addScene(new HelmSceneTest());
	}else{
		// Or Create The weapon Scene
		Game::addScene(new WeaponScene());
	}

	
	// Start the main loop
	Game::run();

	// Debug for memory leaks
	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}