#include "TestScene.h"
#include "irrlicht.h"
#include "Game.h"
#include "Composite.h"
#include "Component.h"

TestScene::TestScene(void):Scene()
{

}

void TestScene::init()
{
	// Create model entity
	Entity* testModel = new Entity(this);
	testModel->createNode("sydney.md2");

	//Set material on model
	//testModel->irrNode->setMaterialTexture( 0, Game::driver->getTexture("../../Irrlicht/Media/sydney.bmp") );
	//testModel->irrNode->setMaterialType( video::EMT_SOLID );

	// Create camera entity
	Entity* camera = new Entity(this);
	camera->node =  sceneManager->addCameraSceneNode(0, vector3df(0,4,-40), vector3df(0,4,0));
	camera->position = vector3df(0,4,-40);
	this->addComponent(camera);
}


TestScene::~TestScene(void)
{
	Scene::~Scene();
}
