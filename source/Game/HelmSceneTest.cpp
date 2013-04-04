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

EnemyDrone* drone1;
EnemyFighter* fighter1;
EnemyAsteroid* asteroid1;
float degree = 0;
EnemyAsteroid* asteroid2;
Enemy* enemy1;

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

	drone1 = new EnemyDrone(irr::core::vector3df(0,0,10));
	//drone1->setAgility(1);
	drone1->velocity = irr::core::vector3df(0,0, 1);
	addComponent(drone1);
	fighter1 = new EnemyFighter(irr::core::vector3df(100,0,0));
	addComponent(fighter1);
	asteroid1 = new EnemyAsteroid(irr::core::vector3df(0,0,0));
	asteroid1->setVelocity(vector3df(0,-0.001f,0));
	addComponent(asteroid1);
	asteroid2 = new EnemyAsteroid(irr::core::vector3df(0,10,0));
	asteroid2->setVelocity(vector3df(0,0.001f,0));
	addComponent(asteroid2);	
	enemy1 = new Enemy();
	enemy1->setPosition(vector3df(0,20,0));
	enemy1->setVelocity(vector3df(0,0.001f,0));
	addComponent(enemy1);
}

void HelmSceneTest::update()
{
	degree+= 0.01f;
	drone1->update();
	drone1->setRotation(irr::core::vector3df(0 , 90, 0));
	drone1->steeRing();
	enemy1->update();	
}

