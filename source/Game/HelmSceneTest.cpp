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

	addComponent(new Player(this));
	addComponent(new Ship(this, vector3df(0,0,0), vector3df(0,0,0)));
	addComponent(manager);
}