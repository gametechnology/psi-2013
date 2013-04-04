#include "HelmSceneTest.h"
#include "HelmStation.h"
#include "Player.h"

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

	addComponent(new Player(this));
}