#include "GameScene.h"
#include "MapGenerator.h"
#include "SectorManager.h"

GameScene::GameScene() : Scene() {

}

void GameScene::onAdd() {
	GalaxyMap* galaxyMap = new GalaxyMap(300, 300, 15);
	addChild(galaxyMap);
	
	galaxyMap.createNewMap(20, 2, 5);
	galaxyMap->transform->position = new vector3df(100, 670, 0);
	
	addComponent(new SectorManager(galaxyMap));
}

void GameScene::init() {
	
}

void GameScene::update() {

}

GameScene::~GameScene() {

}