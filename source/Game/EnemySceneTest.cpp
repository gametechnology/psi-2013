#include "EnemySceneTest.h"

#include "Skybox.h"
#include "EnemyManager.h"

#include <iostream>

EnemySceneTest::EnemySceneTest(void) : Scene()
{
	std::cout<<"CONSTRUCTION";
}

EnemySceneTest::~EnemySceneTest(void)
{
	Scene::~Scene();
}

void EnemySceneTest::init()
{
	Scene::init();

	/////////////////////////////////////////////////////////////////
	//Doesn't work and doesnt use anything of engine, also is obsolete 22-04-2013
	//if using change data please, thank you.
	////////////////////////////////////////////////////////////////
	
	EnemyManager* enemymanager;

	camera = getIrrlichtSceneManager()->addCameraSceneNodeFPS();
	this->light = getIrrlichtSceneManager()->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	
	enemymanager = new EnemyManager();
	addComponent(enemymanager);

	std::cout<<"INIT";
}

void EnemySceneTest::update() {

	std::cout<<"UPDATING je moeder. ja, de bouwvakker";

}