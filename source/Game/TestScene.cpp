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
	Player* player = new Player();
	addChild(player);
	player->handleMessage(DAMAGE, new int(789));	// Send a message to player and components.

	// Create camera entity
	Camera* camera = new Camera();
	camera->transform->velocity->Z -= (float)0.001;
	addChild(camera);
}

TestScene::~TestScene(void)
{
	Scene::~Scene();
}
