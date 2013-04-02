#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "WeaponScene.h"



// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

int main()
{
	bool Isweapon = false;
	// Create engine
	Game game = Game();
	if(Isweapon){
		Game::addScene(new WeaponScene());
		// Create test 
	}else{
		// Or Create The weapon Scene
		Game::addScene(new HelmSceneTest());
	}
	
	// Start the main loop
	Game::run();

	// Debug for memory leaks
	#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}