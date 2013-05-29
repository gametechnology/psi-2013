#include "NebulaSector.h"
#include "Messages.h"

using namespace irr::video;

NebulaSector::NebulaSector(Core* core, SectorManager* parent, std::string skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(core, parent,skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}

void NebulaSector::init(){
	_fog->setColor(SColor(0, 50, 50, 50));
	_fog->setNearDistance(30);
	_fog->setFarDistance(980);
}

void NebulaSector::update(){
	SectorTemplate::update();
}

void NebulaSector::handleMessage(unsigned int message, void* data) {
	delete data;
}

NebulaSector::~NebulaSector() {
	SectorTemplate::~SectorTemplate();
}
