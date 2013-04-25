#include "AsteroidSector.h"
#include "Messages.h"
#include "Engine/IrrlichtNode.h"



AsteroidSector::AsteroidSector(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}
void AsteroidSector::init(){
	for(int i = 0; i < 1000; i++){
		//irr::scene::IMeshSceneNode* cube = Game::getSceneManager()->addCubeSceneNode(2,0,-1,irr::core::vector3df((rand()%500)-250,(rand()%250)-125,(rand()%500)-250),irr::core::vector3df(rand()%90,rand()%90,rand()%90));
		AstroidPlaceholder* ass = new AstroidPlaceholder(this->parent);
		ass->transform->position = &irr::core::vector3df((float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750), (float)((rand() % 1500) - 750));
		ass->transform->rotation = &irr::core::vector3df((float)(rand() % 90), (float)(rand() % 90), (float)(rand() % 90));
		this->addChild(ass);
	}
}

void AsteroidSector::update(){
	SectorTemplate::update();
}

void AsteroidSector::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

AsteroidSector::~AsteroidSector() {
	SectorTemplate::~SectorTemplate();
}


AstroidPlaceholder::AstroidPlaceholder(Composite* parent):Entity() {
	irr::scene::IMeshSceneNode *node = scene->getIrrlichtSceneManager()->addSphereSceneNode(10, 8, 0, -1);
	node->setMaterialFlag(EMF_LIGHTING, false);
	node->setMaterialFlag(EMF_FOG_ENABLE, true);
	node->setMaterialTexture(0, this->game->driver->getTexture("../assets/Textures/SkyBoxes/skybox01.png"));
}

AstroidPlaceholder::~AstroidPlaceholder() {
	Entity::~Entity();
}