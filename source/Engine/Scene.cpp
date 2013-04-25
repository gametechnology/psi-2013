#include <Engine\Scene.h>
#include <Engine\Game.h>

Scene::Scene() : Entity() {
	// Set the state
	state = LOADING;
}

void Scene::onAdd() {
	// Create a scene manager
	sceneManager = this->game->device->getSceneManager();

	Entity::onAdd();
}

Scene::~Scene() {
	
}
