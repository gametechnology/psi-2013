#include "HelmSceneTest.h"

#include "Skybox.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "EnemyFighter.h"
#include "EnemyAsteroid.h"
#include <iostream>

HelmSceneTest::HelmSceneTest(void)
{
}


HelmSceneTest::~HelmSceneTest(void)
{
	Scene::~Scene();
}

//EnemyDrone* drone1;
//EnemyFighter* fighter1;
//EnemyAsteroid* asteroid1;
//EnemyAsteroid* asteroid2;
//Enemy* enemy1;
EnemyManager* enemymanager;

void HelmSceneTest::init()
{
	HelmStation* helmStation = new HelmStation(this);
	addComponent(helmStation);
	filename = "../assets/Textures/SkyBoxes/skybox02.png";
	Skybox* skybox = new Skybox(filename,this);
	addComponent(skybox);
	smgr = Game::getSceneManager();
	camera = smgr->addCameraSceneNodeFPS();
	this->light = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	enemymanager = new EnemyManager();	
	enemymanager->createEnemies();
	addComponent(enemymanager);
}

void HelmSceneTest::update()
{
	Scene::update();
	//enemymanager->update();
}

