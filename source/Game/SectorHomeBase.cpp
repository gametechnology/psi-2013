#include "SectorHomeBase.h"
#include "Messages.h"


SectorHomeBase::SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}
void SectorHomeBase::init(){
	//TODO causes memory leak should create entity's
		BasePlaceholder* base = new BasePlaceholder(this->parent);
		base->position = irr::core::vector3df((rand()%500)-250,(rand()%250)-125,(rand()%500)-250);
		base->orientation = irr::core::vector3df(rand()%90,rand()%90,rand()%90);
		addComponent(base);
	
}

void SectorHomeBase::update(){
	SectorTemplate::update();
}

void SectorHomeBase::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorHomeBase::~SectorHomeBase() {
	SectorTemplate::~SectorTemplate();
}

BasePlaceholder::BasePlaceholder(Composite* parent):Entity(parent) {
	this->node = Game::getSceneManager()->addCubeSceneNode(100,0,-1,irr::core::vector3df((rand()%500)-250,(rand()%250)-125,(rand()%500)-250),irr::core::vector3df(rand()%90,rand()%90,rand()%90));
		
	this->node->setMaterialFlag(EMF_LIGHTING, false);
	this->node->setMaterialFlag(EMF_FOG_ENABLE, true);
	this->node->setMaterialTexture(0,Game::driver->getTexture("../assets/Textures/sand.jpg"));
}

BasePlaceholder::~BasePlaceholder() {
	Entity::~Entity();
}
