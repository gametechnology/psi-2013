#include "BaseSector.h"

BaseSector::BaseSector(Composite* parent, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(parent,skyBoxTexture,boundryRadius,amountWormHoles) {
	init();
}
void BaseSector::init(){
	// Your code here
}

void BaseSector::update(){
	// All the update functionality here
}

void BaseSector::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

BaseSector::~BaseSector() {
	Entity::~Entity();
}
