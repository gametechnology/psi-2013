#include "TestScene.h"
#include "irrlicht.h"
#include "Game.h"
#include "Composite.h"
#include "Component.h"
#include "Player.h"
#include <list>
#include "Messages.h"

TestScene::TestScene(void)
{

}

void TestScene::init()
{
	// Create model entity
	Player* player = new Player(this);
	addComponent(player);
	player->handleMessage(DAMAGE, new int(789));	// Send a message to player and components.

	// Create camera entity
	Entity* camera = new Entity(this);
	camera->node =  sceneManager->addCameraSceneNode(0, vector3df(0,4,-40), vector3df(0,4,0));
	camera->position = vector3df(0,4,-40);
	addComponent(camera);
}

TestScene::~TestScene(void)
{
	Scene::~Scene();
}
