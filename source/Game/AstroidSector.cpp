#include "AstroidSector.h"
#include "Messages.h"


AstroidSector::AstroidSector(Composite* parent, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : SectorTemplate(parent,skyBoxTexture,boundryRadius,amountWormHoles) {
	init();
}
void AstroidSector::init(){
	for(int i=0;i<2500;i++){
		//irr::scene::IMeshSceneNode* cube = Game::getSceneManager()->addCubeSceneNode(2,0,-1,irr::core::vector3df((rand()%500)-250,(rand()%250)-125,(rand()%500)-250),irr::core::vector3df(rand()%90,rand()%90,rand()%90));
		irr::scene::IMeshSceneNode* cube = Game::getSceneManager()->addSphereSceneNode(10,8,0,-1,irr::core::vector3df((rand()%1000)-500,(rand()%1000)-500,(rand()%1000)-500),irr::core::vector3df(rand()%90,rand()%90,rand()%90));
		cube->setMaterialFlag(EMF_LIGHTING, false);
		cube->setMaterialTexture(0,Game::driver->getTexture("../assets/Textures/SkyBoxes/skybox01.png"));
	}
}

void AstroidSector::update(){
	SectorTemplate::update();
}

void AstroidSector::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

AstroidSector::~AstroidSector() {
	Entity::~Entity();
}
