#include "Game.h"
#include "TestScene.h"
#include "Entity.h"

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

	return 0;
}