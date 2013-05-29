#include "BaseSector.h"

BaseSector::BaseSector(Core* core, SectorManager* sectormanager, std::string skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(core, sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();

}
void BaseSector::init(){
	// Your code here

	SectorTemplate::init();
}

void BaseSector::update(){
	// All the update functionality here
	SectorTemplate::update();
}

void BaseSector::handleMessage(unsigned int message, void* data) 
{	
	delete data;
}

BaseSector::~BaseSector() {
	SectorTemplate::~SectorTemplate();
}
