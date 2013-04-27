#include "SectorManager.h"
#include "Messages.h"
#include <algorithm>
#include  "AsteroidSector.h"
#include  "NebulaSector.h"
#include  "SectorHomeBase.h"
#include  "BaseSector.h"

SectorManager::SectorManager(GalaxyMap* map) : Component() {
	_map=map;

	for (int i = 0; i < map->sectors.size(); i++) {
		if(map->sectors[i]->type == HOME_BLUE){
			//delete _mapSector;
			_mapSector = map->sectors[i];
		}
	}
}

void SectorManager::onAdd() {
	//_currentSector = new SectorHomeBase(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
	//printf("[SectorManager] SectorManager onAdd");
	this->getGame()->sceneManager->addScene("SectorHomeBase", new SectorHomeBase(this,"skybox02.png",2000.0,_mapSector->connections.size()));
	activeSceneName = "SectorHomeBase";
}

void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case NEXT_SECTOR: //Switch Sector 
			//Determen which is the new sector
			int index = (int)data;
			std::vector<MapSector*>::iterator temp = _mapSector->connections.begin();
			
			try{
				std::advance(temp,index);
			}catch(char * str){
				printf("[SectorManager] Something went wrong... : %c", str);
			}
			
			_mapSector = *temp;//change the _mapSector to the sector the data tells him to be
			
			// Debug check
			if ( this->getGame()->sceneManager->destroyScene(activeSceneName) )
				printf("Deleted properly");
			else
				printf("No scene deleted");

			//Creates new Sector
			switch (_mapSector->type){ 
				case EMPTY:
					//delete _currentSector;
					printf("[SectorTemplate] EMPTY \n");
					//activeSceneName = "BaseSector";
					//this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case ASTEROID:
					printf("[SectorTemplate] ASTEROID \n");
					//delete _currentSector;
					//activeSceneName = "AsteroidSector";
					//this->getGame()->sceneManager->addScene(activeSceneName,new AsteroidSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case NEBULA:
					printf("[SectorTemplate] NEBULA \n");
					//delete _currentSector;
					//activeSceneName = "NebulaSector";
					//this->getGame()->sceneManager->addScene(activeSceneName,new NebulaSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case SOLAR: 
					printf("[SectorTemplate] SOLAR \n");
					//delete _currentSector;
					//activeSceneName = "BaseSector";
					//this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case HOME_BLUE:
					printf("[SectorTemplate] HOME_BLUE \n");
					//delete _currentSector;
					//activeSceneName = "SectorHomeBase";
					//this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case HOME_RED:
					printf("[SectorTemplate] HOME_RED \n");
					//delete _currentSector;
					//activeSceneName = "SectorHomeBase";
					//this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
			}

			break;
	}
	//delete data;
}

SectorManager::~SectorManager() {
	
}
