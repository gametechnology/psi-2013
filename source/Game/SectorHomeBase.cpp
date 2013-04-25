#include "SectorHomeBase.h"
#include "Messages.h"


SectorHomeBase::SectorHomeBase(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}
void SectorHomeBase::onAdd(){
	//TODO causes memory leak should create entity's
	BasePlaceholder* base = new BasePlaceholder();
	addChild(base);
	base->transform->position = new irr::core::vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250));
	base->transform->rotation = new irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90));
	
	Scene::onAdd();
}

void SectorHomeBase::update() {
	SectorTemplate::update();
}

void SectorHomeBase::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorHomeBase::~SectorHomeBase() {
	SectorTemplate::~SectorTemplate();
}

BasePlaceholder::BasePlaceholder() : Entity() {
	
}

void BasePlaceholder::onAdd() {
	irr::scene::IMeshSceneNode *node = scene->getIrrlichtSceneManager()->addCubeSceneNode(100, 0, -1,
		irr::core::vector3df((float)((rand() % 500) - 250), (float)((rand() % 250) - 125), (float)((rand() % 500) - 250)),
		irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90))
	);
		
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialFlag(EMF_FOG_ENABLE, true);
	node->setMaterialTexture(0, game->driver->getTexture("../assets/Textures/sand.jpg"));

	Entity::onAdd();
}

BasePlaceholder::~BasePlaceholder() {
	Entity::~Entity();
}
