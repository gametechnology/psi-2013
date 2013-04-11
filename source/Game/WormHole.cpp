#include "WormHole.h"
#include "Engine/Game.h"

WormHole::WormHole(Composite* parent, unsigned int id, irr::core::vector3df position) : Entity(parent) {
	// Setting id and position
	this->id = id;
	this->position = position;
	
	// Creating a 2d Node in 3d space that always looks straight to the camera, irlicht functionalitie.
	_wormhole = Game::getSceneManager()->addBillboardSceneNode(0, irr::core::dimension2df(80.0f,100.0f), position );
	
	// Setting materials
	_wormhole->setMaterialFlag(EMF_LIGHTING, false);
	_wormhole->setMaterialFlag(EMF_FOG_ENABLE, true);
	_wormhole->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	// Setting Texture
	const char* filePath = "../assets/Textures/Wormholes/WormHole.png";
	_wormhole->setMaterialTexture(0, Game::driver->getTexture( filePath ));
}
// Needs setPosition because else te node will not get moved
void WormHole::setPosition(irr::core::vector3df &newPos){
	this->position = position;
	_wormhole->setPosition( position );
}

// Added update for possible annimations
void WormHole::update(){
	Entity::update();
}

void WormHole::handleMessage(unsigned int message, void* data) {
	delete data;
}

WormHole::~WormHole() {
	Entity::~Entity();
}
