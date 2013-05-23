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

void SectorManager::update() { 
	
}

void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case NEXT_SECTOR: //Switch Sector 
			cout << "yeah" << endl;
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

			// Deleting Scene
			this->getGame()->sceneManager->deactivateScene( activeSceneName );
				printf("deactivated properly\n");
				//printf("No scene deleted");

			//Creates new Sector
			switch (_mapSector->type){ 
				case EMPTY:
					//delete _currentSector;
					printf("[SectorTemplate] EMPTY \n");
					activeSceneName = "BaseSector";
					this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case ASTEROID:
					printf("[SectorTemplate] ASTEROID \n");
					//delete _currentSector;
					activeSceneName = "AsteroidSector";
					this->getGame()->sceneManager->addScene(activeSceneName,new AsteroidSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case NEBULA:
					printf("[SectorTemplate] NEBULA \n");
					//delete _currentSector;
					activeSceneName = "NebulaSector";
					this->getGame()->sceneManager->addScene(activeSceneName,new NebulaSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case SOLAR: 
					printf("[SectorTemplate] SOLAR \n");
					//delete _currentSector;
					activeSceneName = "BaseSector";
					this->getGame()->sceneManager->addScene(activeSceneName,new BaseSector(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case HOME_BLUE:
					printf("[SectorTemplate] HOME_BLUE \n");
					//delete _currentSector;
					this->_ship->setBackAtOwnBase();
					activeSceneName = "SectorHomeBase";
					this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
				case HOME_RED:
					printf("[SectorTemplate] HOME_RED \n");
					//delete _currentSector;
					this->_ship->setFoundEnemyBase();
					activeSceneName = "SectorHomeBase";
					this->getGame()->sceneManager->addScene(activeSceneName,new SectorHomeBase(this,"skybox02.png",2000.0,_mapSector->connections.size()));
					break;
			}
			
			this->getGame()->sceneManager->destroyScene( tempName );
			
			break;
	}
	//delete data;
}
Ship* SectorManager::getShip(){
	return _ship;
}
SectorManager::~SectorManager() {
	
}
