#include "SectorManager.h"
#include "Messages.h"

SectorManager::SectorManager(Composite* parent) : Entity(parent) {
	
}
void SectorManager::init(){
	_currentSector = new SectorTemplate(this->parent,"..\..\assets\Textures\SkyBoxes\skybox01.png",20.0);
	SectorManager::addComponent(_currentSector);
}
void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case NEXT_SECTOR: /* Switch Sector */
			delete _currentSector;
			_currentSector = new SectorTemplate(this->parent,"..\..\assets\Textures\SkyBoxes\skybox01.png",20.0);
			SectorManager::addComponent(_currentSector);

			break;
	}
	delete data;
}

SectorManager::~SectorManager() {
	Entity::~Entity();

}
