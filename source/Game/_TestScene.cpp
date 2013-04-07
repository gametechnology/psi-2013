#include "TestScene.h"
#include "Irrlicht/irrlicht.h"
#include "Engine/Game.h"
#include "Engine/Composite.h"
#include "Engine/Component.h"
#include "Player.h"
#include "Engine/Camera.h"
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
	Camera* camera = new Camera(this, vector3df(0,4,-4), vector3df(0,4,0));
	camera->velocity.Z -= 0.001;
	addComponent(camera);
}

TestScene::~TestScene(void)
{
	Scene::~Scene();
}