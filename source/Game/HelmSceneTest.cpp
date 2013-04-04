#include "HelmSceneTest.h"
#include "Player.h"
#include "Ship.h"

HelmSceneTest::HelmSceneTest(void) {}
HelmSceneTest::~HelmSceneTest(void) { Scene::~Scene(); }

void HelmSceneTest::init()
{
	addComponent(new Player(this));
	//addComponent(new Ship(this));
}