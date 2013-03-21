#include "SectorManager.h"
#include "Messages.h"

SectorManager::SectorManager(Composite* parent) : Entity(parent) {
	
}

void SectorManager::handleMessage(unsigned int message, void* data) {
	switch(message) {
		case DAMAGE: /* Do something */;
	}
	delete data;
}

SectorManager::~SectorManager() {
	Entity::~Entity();

}
