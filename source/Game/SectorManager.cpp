#include "SectorManager.h"
#include "Messages.h"
#include <algorithm>

SectorManager::SectorManager(GalaxyMap* map) : Scene() {
	_map=map;
	for(std::list<MapSector*>::iterator i = map->sectors.begin(); i != map->sectors.end(); ++i)
	{
		if((*i)->type == HOME_BLUE){
			//delete _mapSector;
			_mapSector = (*i);
		}
	}
	//init();
}
void SectorManager::init(){
	_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
	SectorManager::addComponent(_currentSector);
}
void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case NEXT_SECTOR: /* Switch Sector */
			std::list<MapSector*>::iterator temp = std::find(_mapSector->connections.begin(),_mapSector->connections.end(),data);
			
			_mapSector = *temp;//change the _mapSector to the sector the data tells him to be

			switch (_mapSector->type){ 
				case EMPTY:
					delete _currentSector;
					_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
					SectorManager::addComponent(_currentSector);
					break;
				case ASTEROID:
					delete _currentSector;
					_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
					SectorManager::addComponent(_currentSector);
					break;
				case NEBULA:
					delete _currentSector;
					_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
					SectorManager::addComponent(_currentSector);
					break;
				case SOLAR: 
					delete _currentSector;
					_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
					SectorManager::addComponent(_currentSector);
					break;
				case HOME_BLUE:
					delete _currentSector;
					_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
					SectorManager::addComponent(_currentSector);
					break;
				case HOME_RED:
					delete _currentSector;
					_currentSector = new SectorTemplate(this->parent,"../assets/Textures/SkyBoxes/skybox02.png",20.0,_mapSector->connections.size());
					SectorManager::addComponent(_currentSector);
					break;
			}

			break;
	}
	delete data;
}

SectorManager::~SectorManager() {
	Scene::~Scene();

}
