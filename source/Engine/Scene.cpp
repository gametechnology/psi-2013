#include <Engine\Scene.h>

Scene::Scene(const char* name) : Composite(name)
{
	/*
	* This doesn't do jack on its own.
	* That's why you have to extend it for your own scenes!
	*/
}

void Scene::init()
{
	Composite::init();
}

void Scene::update()
{
	Composite::update();
}

void Scene::draw()
{
	Composite::draw();
}

void Scene::addComponent(Component* component)
{
	Composite::addComponent(component);
}

void Scene::removeComponent(Component* component)
{
	Composite::removeComponent(component);
}