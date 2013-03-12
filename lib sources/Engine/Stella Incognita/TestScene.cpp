#include "TestScene.h"
#include "irrlicht.h"
#include "Game.h"
#include "Composite.h"

TestScene::TestScene(void)
{

}

void TestScene::Init()
{
	// Get the mesh
	irr::scene::IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");

	// Create model entity
	Entity* testModel = new Entity();
	testModel->irrNode =  smgr->addMeshSceneNode( mesh );
	this->AddComponent(testModel);

	//Set material on model
	//testModel->irrNode->setMaterialTexture( 0, Game::driver->getTexture("../../Irrlicht/Media/sydney.bmp") );
	//testModel->irrNode->setMaterialType( video::EMT_SOLID );

	// Create camera entity
	Entity* camera = new Entity();
	camera->irrNode =  smgr->addCameraSceneNode(0, vector3df(0,4,-40), vector3df(0,4,0));
	this->AddComponent(camera);
}


TestScene::~TestScene(void)
{
	delete testModel;
	delete camera;

	// TODO: use a loop to remove all entity
}
