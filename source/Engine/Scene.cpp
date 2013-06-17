#include <Engine\Scene.h>
#include <Engine\Game.h>

Scene::Scene() : Entity() {
	// Set the state
	state = LOADING;
}

void Scene::onAdd() {
	Entity::onAdd();
}

void Scene::addGuiElements()
{

}

irr::scene::ISceneManager* Scene::getIrrlichtSceneManager() {
	if (game->device == NULL)
	{
		printf("device doesn't exists");
	}
	return game->device->getSceneManager();
}

Scene::~Scene() {
	Entity::~Entity();
}
