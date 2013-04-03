#include "AstroidSector.h"
#include "Messages.h"


AstroidSector::AstroidSector(Composite* parent, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(parent,skyBoxTexture,boundryRadius,amountWormHoles) {
	init();
}
void AstroidSector::init(){
	for(int i=0;i<10;i++){
		irr::scene::IMeshSceneNode* cube = Game::getSceneManager()->addCubeSceneNode(2,0,-1,irr::core::vector3df((rand()%100)-50,(rand()%50)-25,(rand()%100)-50),irr::core::vector3df(rand()%10,rand()%5,rand()%10));
		cube->setMaterialFlag(EMF_LIGHTING, false);
		cube->setMaterialTexture(0,Game::driver->getTexture("../assets/Textures/SkyBoxes/skybox01.png"));
	}
}

void AstroidSector::update(){
	
}

void AstroidSector::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

AstroidSector::~AstroidSector() {
	Entity::~Entity();
}
