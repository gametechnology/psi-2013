#include "SectorManager.h"
#include "Messages.h"
#include <algorithm>
#include  "AsteroidSector.h"
#include  "NebulaSector.h"
#include  "SectorHomeBase.h"
#include  "BaseSector.h"

SectorManager::SectorManager(GalaxyMap* map,Ship* ship) : Component() {
	_map=map;
	_ship=ship;
	printf("!!![SectorManager] _map->sectors.size(): %i \n",_map->sectors.size());
	for (unsigned int i = 0; i < _map->sectors.size(); i++) {
			printf("!!![SectorManager] whats mapID: %i \n",_map->sectors[i]->getId());
		if(_map->sectors[i]->type == HOME_BLUE){
			//delete _mapSector;
			_mapSector = _map->sectors[i];
		}
	}
}

void SectorManager::onAdd() {
	activeSceneName = "SectorHomeBase";
	printf("[SectorManager] %s",_mapSector->skyboxTexture);
	this->getGame()->sceneManager->addScene(activeSceneName, new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
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
			
			char * tempName = activeSceneName;

			// Checks if the scene is destroyed 
			if ( this->getGame()->sceneManager->destroyScene( tempName ) ) {
				
				// Turn Around the ship and place it closer to the center so it does not come in a endless loop of wormhole transitions
				_ship->transform->position->setLength( _ship->transform->position->getLength() * 0.8 );
				_ship->transform->rotation->rotateXZBy( PI * 180 );


				//Creates new Sector
				switch (_mapSector->type){ 
					case EMPTY:
						//delete _currentSector;
						printf("[SectorTemplate] EMPTY \n");
						activeSceneName = "BaseSector";
						this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
						break;
					case ASTEROID:
						printf("[SectorTemplate] ASTEROID \n");
						//delete _currentSector;
						activeSceneName = "AsteroidSector";
						this->getGame()->sceneManager->addScene(activeSceneName,new AsteroidSector(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
						break;
					case NEBULA:
						printf("[SectorTemplate] NEBULA \n");
						//delete _currentSector;
						activeSceneName = "NebulaSector";
						this->getGame()->sceneManager->addScene(activeSceneName,new NebulaSector(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
						break;
					case SOLAR: 
						printf("[SectorTemplate] SOLAR \n");
						//delete _currentSector;
						activeSceneName = "BaseSector";
						this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
						break;
					case HOME_BLUE:
						printf("[SectorTemplate] HOME_BLUE \n");
						//delete _currentSector;
						activeSceneName = "SectorHomeBase";
						this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
						break;
					case HOME_RED:
						printf("[SectorTemplate] HOME_RED \n");
						//delete _currentSector;
						activeSceneName = "SectorHomeBase";
						this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,_mapSector->skyboxTexture,2000.0,_mapSector->connections.size()));
						break;
				}		
			}
			


			break;
	}
	//delete data;
}
Ship* SectorManager::getShip(){
	return _ship;
}
SectorManager::~SectorManager() {
	
}
