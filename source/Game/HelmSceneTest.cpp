#include "HelmSceneTest.h"
#include "Player.h"
#include "Ship.h"
#include "EnemyManager.h"

HelmSceneTest::HelmSceneTest(void) {}
HelmSceneTest::~HelmSceneTest(void) { Scene::~Scene(); }


void HelmSceneTest::init()
{
	
	EnemyManager* manager;
	manager = new EnemyManager();
	//ICameraSceneNode* camera = Game::getSceneManager()->addCameraSceneNodeFPS();
	//addComponent(new Player(this));
	addComponent(new Ship(this));
	addComponent(manager);
}