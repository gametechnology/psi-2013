#include "HelmSceneTest.h"


HelmSceneTest::HelmSceneTest(void)
{
}


HelmSceneTest::~HelmSceneTest(void)
{
	Scene::~Scene();
}

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

	drone1 = new Enemy();
	drone1->createNode("../assets/Models/Cube.3ds");
	drone1->position = irr::core::vector3df(-100,0,0);
	addComponent(drone1);
}

void HelmSceneTest::update()
{
	drone1->update();
}