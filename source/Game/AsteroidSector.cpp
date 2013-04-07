#include "AsteroidSector.h"
#include "Messages.h"


AsteroidSector::AsteroidSector(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(sectormanager, skyBoxTexture,boundryRadius,amountWormHoles) {
	//init();
}
void AsteroidSector::init(){
	for(int i=0;i<1000;i++){
		//irr::scene::IMeshSceneNode* cube = Game::getSceneManager()->addCubeSceneNode(2,0,-1,irr::core::vector3df((rand()%500)-250,(rand()%250)-125,(rand()%500)-250),irr::core::vector3df(rand()%90,rand()%90,rand()%90));
		AstroidPlaceholder* ass = new AstroidPlaceholder(this->parent);
		ass->position = irr::core::vector3df((rand()%1500)-750,(rand()%1500)-750,(rand()%1500)-750);
		ass->orientation = irr::core::vector3df(rand()%90,rand()%90,rand()%90);
		addComponent(ass);
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


AstroidPlaceholder::AstroidPlaceholder(Composite* parent):Entity(parent) {
	this->node = Game::getSceneManager()->addSphereSceneNode(10,8,0,-1);
	this->node->setMaterialFlag(EMF_LIGHTING, false);
	this->node->setMaterialFlag(EMF_FOG_ENABLE, true);
	this->node->setMaterialTexture(0,Game::driver->getTexture("../assets/Textures/SkyBoxes/skybox01.png"));
}

AstroidPlaceholder::~AstroidPlaceholder() {
	Entity::~Entity();
}