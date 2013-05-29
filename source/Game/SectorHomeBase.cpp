#include "SectorHomeBase.h"

using namespace irr;
using namespace irr::core;
using namespace irr::video;

SectorHomeBase::SectorHomeBase(Core* core, SectorManager* sectormanager, std::string skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(core, sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	_core = core;
}
void SectorHomeBase::init(){
	//TODO causes memory leak should create entity's
	BasePlaceholder* base = new BasePlaceholder(_core);
	addComponent(base);

	base->setPosition(new vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250)));
	base->setRotation(new vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90)));

	SectorTemplate::init();
}

void SectorHomeBase::update() {
	SectorTemplate::update();
}

//void SectorHomeBase::handleMessage(unsigned int message, void* data) {
//	
//	delete data;
//}

SectorHomeBase::~SectorHomeBase() {
	SectorTemplate::~SectorTemplate();
}

BasePlaceholder::BasePlaceholder(Core* core) : GameObject() 
{
	_core = core;
}

void BasePlaceholder::init() {
	PrimitiveComponent* cube;

	cube = new PrimitiveComponent(_core->getSmgr(), PrimitiveComponent::PRIM_CUBE, 2, 
		vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750)));

	addComponent(cube);

	cube->getNode()->setMaterialFlag(EMF_LIGHTING, false);
	cube->getNode()->setMaterialFlag(EMF_FOG_ENABLE, true);
	cube->getNode()->setMaterialTexture(0, _core->getDriver()->getTexture("../assets/Textures/sand.jpg"));
}

BasePlaceholder::~BasePlaceholder() 
{
	node->remove();
}
