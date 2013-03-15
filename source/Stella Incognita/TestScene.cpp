#include "TestScene.h"
#include "irrlicht.h"
#include "Game.h"
#include "Composite.h"
#include "Component.h"
#include <list>

TestScene::TestScene(void)
{

}

void TestScene::init()
{
	// Create model entity
	Entity* testModel = new Entity(this);
	testModel->createNode("sydney.md2");

	// Create camera entity
	Entity* camera = new Entity(this);
	camera->node =  sceneManager->addCameraSceneNode(0, vector3df(0,4,-40), vector3df(0,4,0));
	this->addComponent(camera);
}


TestScene::~TestScene(void)
{
	//Remove all entities from the scene list
	for(std::list<Component*>::iterator i = components.begin(); i != components.end(); ++i )
	{
		delete (*i);
	}
}
