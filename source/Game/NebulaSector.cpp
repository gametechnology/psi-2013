#include "NebulaSector.h"
#include "Messages.h"

NebulaSector::NebulaSector(SectorManager* parent, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(parent,skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}

void NebulaSector::init(){
	_fog->SetColor(SColor(0, 50, 50, 50));
	_fog->SetNearDistance(30);
	_fog->SetFarDistance(980);
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
