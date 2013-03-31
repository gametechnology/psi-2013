#include "HelmSceneTest.h"
#include "HelmStation.h"
#include "Skybox.h"
#include "Enemy.h"

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
	//irr::video::ITexture* texture = drvr->getTexture("D:\\Github\\psi-2013\\assets\\Textures\\SkyBoxes\\skybox2.png");
	//smgr->addSkyDomeSceneNode(texture);
	//addComponent(smgr);
	//irr::io::path filename;
	filename = "../assets/Textures/SkyBoxes/skybox02.png";
	Skybox* skybox = new Skybox(filename,this);
	addComponent(skybox);
	irr::scene::ISceneManager* smgr = Game::getSceneManager();
	irr::scene::ICameraSceneNode * camera = smgr->addCameraSceneNodeFPS();
	Enemy* drone1 = new Enemy();
	drone1->createNode("../assets/Models/Cube.3ds");
	drone1->setPosition(irr::core::vector3df(0,0,0));
	drone1->position = drone1->getPosition();
	addComponent(drone1);
}