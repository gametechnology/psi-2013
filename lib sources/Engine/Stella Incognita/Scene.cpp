#include "Scene.h"
#include "Game.h"


Scene::Scene()
{
	// Set the state
	state = LOADING;
	// Create a scene manager
	smgr = Game::device->getSceneManager();
}


Scene::~Scene()
{
}
