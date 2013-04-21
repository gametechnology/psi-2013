#include "EnemySceneTest.h"

#include "Skybox.h"
#include "EnemyManager.h"

EnemySceneTest::EnemySceneTest(void)
{
}


EnemySceneTest::~EnemySceneTest(void)
{
	Scene::~Scene();
}


void EnemySceneTest::init()
{
	EnemyManager* enemymanager;
	camera = this->game->getSceneManager()->addCameraSceneNodeFPS();
	this->light = this->game->getSceneManager()->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	enemymanager = new EnemyManager();	
	enemymanager->createEnemies();
	addChild(enemymanager);
}