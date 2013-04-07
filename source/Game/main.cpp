#include "Engine/Game.h"
#include "HelmSceneTest.h"
#include "EnemySceneTest.h"
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

	//Game::client->setupClient("145.92.13.97");

	// Create test scene
	Game::addScene(new HelmSceneTest());
	//change the scenes by commenting the other scenes and uncomment the one with the enemysceneTest for the enemies
	//Game::addScene(new EnemySceneTest());
	
	// Start the main loop
	Game::run();

	return 0;
}