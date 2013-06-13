#include "SectorHomeBase.h"
#include "Messages.h"
#include "MapSector.h"


SectorHomeBase::SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles, int type) : SectorTemplate(sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
	_type = type;
}
void SectorHomeBase::onAdd(){
	//TODO causes memory leak should create entity's
	BasePlaceholder* base = new BasePlaceholder(_type);
	addChild(base);
	base->transform->position = new irr::core::vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250));
	base->transform->rotation = new irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90));
	
	SectorTemplate::onAdd();
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

BasePlaceholder::BasePlaceholder(int type) : Entity() {
	 _type = type;
}

void BasePlaceholder::onAdd() {
	node = scene->getIrrlichtSceneManager()->addCubeSceneNode(100, 0, -1,
		irr::core::vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250)),
		irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90))
	);
		
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialFlag(EMF_FOG_ENABLE, true);
	node->setMaterialTexture(0, game->driver->getTexture("../assets/Textures/HomeBase/white.jpg"));

	if (_type == (typeSector(HOME_BLUE)))
		node->setMaterialTexture(0, game->driver->getTexture("../assets/Textures/HomeBase/blue.jpg"));
	else if (_type == (typeSector(HOME_RED)))
		node->setMaterialTexture(0, game->driver->getTexture("../assets/Textures/HomeBase/red.jpg"));

	Entity::onAdd();
}

BasePlaceholder::~BasePlaceholder() {
	node->remove();
	Entity::~Entity();
}
