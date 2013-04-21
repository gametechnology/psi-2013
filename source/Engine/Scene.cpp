#include <Engine\Scene.h>
#include <Engine\Game.h>

Scene::Scene() : Entity() {
	// Set the state
	state = LOADING;

	// Create a scene manager
	sceneManager = Entity::game->device->getSceneManager();

	// Scene is enabled
	//enabled = true;
}

Scene::~Scene() {
	
}
