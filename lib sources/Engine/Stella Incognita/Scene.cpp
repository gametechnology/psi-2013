#include "Scene.h"
#include "Game.h"

Scene::Scene()
{
	// Set the state
	state = LOADING;

	// Create a scene manager
	sceneManager = Game::device->getSceneManager();

	// Scene is enabled
	//enabled = true;
}

Scene::~Scene()
{
}