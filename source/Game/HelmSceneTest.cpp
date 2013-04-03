#include "HelmSceneTest.h"
#include "HelmStation.h"
#include "Skybox.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"

HelmSceneTest::HelmSceneTest(void)
{
}


HelmSceneTest::~HelmSceneTest(void)
{
	Scene::~Scene();
}

Enemy* drone1;

void HelmSceneTest::init()
{
	HelmStation* helmStation = new HelmStation(this);
	addComponent(helmStation);
	filename = "../assets/Textures/SkyBoxes/skybox02.png";
	Skybox* skybox = new Skybox(filename,this);
	addComponent(skybox);
	irr::scene::ISceneManager* smgr = Game::getSceneManager();
	irr::scene::ICameraSceneNode * camera = smgr->addCameraSceneNodeFPS();
	this->light = smgr->addLightSceneNode(0,vector3df(5000,5000,5000),SColor(100,100,100,255),100000);
	drone1 = new EnemyDrone(irr::core::vector3df(100,0,0));
	//drone1 = new Enemy();
	//drone1->createNode("../assets/Models/Space_Drone.dae");
	
	//positioning doesn't work
	//drone1->setPosition(irr::core::vector3df(100,0,0));
	//drone1->chase(irr::core::vector3df(500,0,0));

	addComponent(drone1);
}

void HelmSceneTest::update()
{

}

