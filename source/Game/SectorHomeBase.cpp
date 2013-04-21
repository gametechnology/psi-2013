#include "SectorHomeBase.h"
#include "Messages.h"


SectorHomeBase::SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}
void SectorHomeBase::init(){
	//TODO causes memory leak should create entity's
		BasePlaceholder* base = new BasePlaceholder(this->parent);
		base->transform->position = &irr::core::vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250));
		base->transform->rotation = &irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90));
		addChild(base);
	
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
	this->node = game->getSceneManager()->addCubeSceneNode(100, 0, -1,
		irr::core::vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250)),
		irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90))
	);
		
	this->node->setMaterialFlag(EMF_LIGHTING, false);
	this->node->setMaterialFlag(EMF_FOG_ENABLE, true);
	this->node->setMaterialTexture(0,game->driver->getTexture("../assets/Textures/sand.jpg"));
}

BasePlaceholder::~BasePlaceholder() {
	Entity::~Entity();
}
