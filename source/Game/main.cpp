#include <Engine/Game.h>
#include <Irrlicht/driverChoice.h>

#include "EnemySceneTest.h"
#include "MainMenuScene.h"
#include "GameScene.h"

#include "NetworkInterface.h"
#include "EmptyTestScene.h"


// Include memory leak detection files.
#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
	// Create engine
	Game* game = new Game();
	//Enemy::newEnemyId = 0;
	//Add the MainMenu
	//Scene* scene = new EnemySceneTest();
	Scene* scene = new MainMenuScene();
	game->sceneManager->addScene("MainMenuScene", scene);

	//Create ship
	//Ship* ship = new Ship(irr::core::vector3df(0,0,0), irr::core::vector3df(0,0,0));
	//scene->addChild(ship);
	Game::addScene(new EnemySceneTest());
	// Initialize game
	game->init();

	// Start the main loop
	game->run();

	// Debug for memory leaks
	#ifdef _DEBUG
	//_CrtDumpMemoryLeaks();
	#endif

	return 0;
}