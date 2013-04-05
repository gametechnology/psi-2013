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
	drone1->setVelocity(vector3df(0.005f,0,0));
	drone1->setRotation(irr::core::vector3df(0,1,0));
	addComponent(drone1);
	fighter1 = new EnemyFighter(irr::core::vector3df(100,0,0));
	fighter1->setVelocity(vector3df(0.005f,0,0));
	fighter1->setRotation(irr::core::vector3df(0,1,0));
	addComponent(fighter1);
	asteroid1 = new EnemyAsteroid(irr::core::vector3df(0,0,0),vector3df(0,0.005f,0));
	addComponent(asteroid1);
	asteroid2 = new EnemyAsteroid(irr::core::vector3df(0,10,0),vector3df(0,-0.005f,0));
	addComponent(asteroid2);
}

void HelmSceneTest::update()
{
	drone1->steeRing();
	drone1->update();
	fighter1->steeRing();
	fighter1->update();
	asteroid1->update();
	asteroid2->update();
	asteroid1->contactGenerator(asteroid2);
	asteroid2->contactGenerator(asteroid1);
}

