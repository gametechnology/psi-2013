#include "SectorManager.h"
#include "Messages.h"
#include <algorithm>
#include  "AsteroidSector.h"
#include  "NebulaSector.h"
#include  "SectorHomeBase.h"
#include  "BaseSector.h"
SectorManager::SectorManager(GalaxyMap* map) {
	_map=map;
	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if((*i)->type == HOME_BLUE){
			//delete _mapSector;
			_mapSector = (*i);
		}
	}
}
void SectorManager::init(){
	//_currentSector = new SectorHomeBase(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
	Game::addScene(new SectorHomeBase(this,"skybox02.png",200.0,_mapSector->connections.size()));
}
void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case NEXT_SECTOR: //Switch Sector 
			//Determen which is the new sector
			int index = (int)data;
			std::list<MapSector*>::iterator temp = _mapSector->connections.begin();
			try{
				std::advance(temp,index);
			}catch(char * str){
				printf("[SectorManager] Something went wrong... : %c", str);
			}
			_mapSector = *temp;//change the _mapSector to the sector the data tells him to be
			Game::removeScene();
			//Creates new Sector
			switch (_mapSector->type){ 
				case EMPTY:
					//delete _currentSector;
					printf("[SectorTemplate] EMPTY \n");
					Game::addScene(new BaseSector(this,"skybox02.png",200.0,_mapSector->connections.size()));
					break;
				case ASTEROID:
					printf("[SectorTemplate] ASTEROID \n");
					//delete _currentSector;
					Game::addScene(new AsteroidSector(this,"skybox02.png",200.0,_mapSector->connections.size()));
					break;
				case NEBULA:
					printf("[SectorTemplate] NEBULA \n");
					//delete _currentSector;
					Game::addScene(new NebulaSector(this,"skybox02.png",200.0,_mapSector->connections.size()));
					break;
				case SOLAR: 
					printf("[SectorTemplate] SOLAR \n");
					//delete _currentSector;
					Game::addScene(new BaseSector(this,"skybox02.png",200.0,_mapSector->connections.size()));
					break;
				case HOME_BLUE:
					printf("[SectorTemplate] HOME_BLUE \n");
					//delete _currentSector;
					Game::addScene(new SectorHomeBase(this,"skybox02.png",200.0,_mapSector->connections.size()));
					break;
				case HOME_RED:
					printf("[SectorTemplate] HOME_RED \n");
					//delete _currentSector;
					Game::addScene(new SectorHomeBase(this,"skybox02.png",200.0,_mapSector->connections.size()));
					break;
			}

			break;
	}
	//delete data;
}

SectorManager::~SectorManager() {
	
}
