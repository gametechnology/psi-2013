#include "GameScene.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Shipmap.h"
#include "ObjectPool.h"
#include "Laser.h"

GameScene::GameScene() : Scene() {

}

void GameScene::onAdd() {
	ObjectPool<Laser>* laserPool = new ObjectPool<Laser>(50);
	EnemyFighter::laserPool = *laserPool;
	GalaxyMap* galaxyMap = new GalaxyMap(300, 300, 15);
	
	galaxyMap->createMap(20, 2, 5);
	galaxyMap->transform->position = new vector3df(100, 670, 0);
	printf("-----------Added SectorManager----------\n\n");
	addComponent(new SectorManager(galaxyMap));

	_shipmap = new Shipmap(this);
	addChild(_shipmap);

}

void GameScene::init() {
	Scene::init();
}

void GameScene::update() {
	Scene::update();
}

void GameScene::switchStation(StationType type)
{
	this->removeChild(_shipmap);

	switch(type)
	{
		case ST_DEFENCE:
			break;
		case ST_HELM:
			break;
		case ST_NAVIGATION:
			break;
		case ST_POWER:
			break;
		case ST_WEAPON:
			break;
	}
}

GameScene::~GameScene() {

}
