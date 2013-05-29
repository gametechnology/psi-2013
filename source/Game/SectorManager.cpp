#include "SectorManager.h"
#include "GameScene.h"

SectorManager::SectorManager(GameScene* gameScene, Core* core, GalaxyMap* map,Ship* ship) : Composite("SectorManager") 
{
	_map=map;
	_ship=ship;
	_gameScene = gameScene;
	_core = core;

	for(std::list<MapSector*>::iterator it = map->getSectors()->begin(); it != map->getSectors()->end(); it++)
	{
		if((*it)->type == HOME_BLUE){
			_mapSector = (*it);
		}
	}

	init();
}

void SectorManager::init() {
	_activeSector = new SectorHomeBase(_core, this, "sky", 2000.0, _mapSector->connections.size());
	addComponent(_activeSector);	

	Composite::init();
}

void SectorManager::update()
{
	Composite::update();
}

void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
	case NEXT_SECTOR: 
		int index = (int)data;
		std::vector<MapSector*>::iterator temp = _mapSector->connections.begin();

		try{
			std::advance(temp,index);
		}catch(char * str){
			printf("[SectorManager] Something went wrong... : %c", str);
		}

		_mapSector = *temp;

		switch (_mapSector->type){ 
		case EMPTY:
			printf("[SectorTemplate] EMPTY \n");
			removeComponent(_activeSector);
			delete _activeSector;
			_activeSector = new BaseSector(_core, this,"skybox02.png",2000.0,_mapSector->connections.size());
			addComponent(_activeSector);
			break;
		case ASTEROID:
			printf("[SectorTemplate] ASTEROID \n");
			removeComponent(_activeSector);
			delete _activeSector;
			_activeSector = new AsteroidSector(_core, this,"skybox02.png",2000.0,_mapSector->connections.size());
			addComponent(_activeSector);
			break;
		case NEBULA:
			printf("[SectorTemplate] NEBULA \n");
			removeComponent(_activeSector);
			delete _activeSector;
			_activeSector = new NebulaSector(_core, this,"skybox02.png",2000.0,_mapSector->connections.size());
			addComponent(_activeSector);
			break;
		case SOLAR: 
			printf("[SectorTemplate] SOLAR \n");
			removeComponent(_activeSector);
			delete _activeSector;
			_activeSector = new BaseSector(_core, this,"skybox02.png",2000.0,_mapSector->connections.size());
			addComponent(_activeSector);
			break;
		case HOME_BLUE:
			printf("[SectorTemplate] HOME_BLUE \n");
			removeComponent(_activeSector);
			delete _activeSector;
			_activeSector = new SectorHomeBase(_core, this,"skybox02.png",2000.0,_mapSector->connections.size());
			addComponent(_activeSector);
			break;
		case HOME_RED:
			printf("[SectorTemplate] HOME_RED \n");
			removeComponent(_activeSector);
			delete _activeSector;
			_activeSector = new SectorHomeBase(_core, this,"skybox02.png",2000.0,_mapSector->connections.size());
			addComponent(_activeSector);
			break;
		}
	}
}

SectorManager::~SectorManager() {

}
