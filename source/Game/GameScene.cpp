#include "GameScene.h"
#include "MapGenerator.h"
#include "SectorManager.h"
#include "Shipmap.h"

GameScene::GameScene() : Scene() {

}

void GameScene::onAdd() {
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
		case StationType::ST_DEFENCE:
			break;
		case StationType::ST_HELM:
			break;
		case StationType::ST_NAVIGATION:
			break;
		case StationType::ST_POWER:
			break;
		case StationType::ST_WEAPON:
			break;
	}
}

GameScene::~GameScene() {

}
