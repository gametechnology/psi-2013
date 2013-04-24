#include <Engine\Scene.h>
#include <Engine\Game.h>

Scene::Scene() : Entity() {
	// Set the state
	state = LOADING;
}

void Scene::onAdd() {
	Entity::onAdd();

	// Create a scene manager
	sceneManager = this->game->device->getSceneManager();
}

Scene::~Scene() {
	
}
