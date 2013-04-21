#include "WormHole.h"
#include "Engine/Game.h"

WormHole::WormHole(Composite* parent, unsigned int id, irr::core::vector3df position) : Entity() {
	// Setting id and position
	this->id = id;
	this->transform->position = &position;
	
	// Creating a 2d Node in 3d space that always looks straight to the camera, irlicht functionalitie.
	_wormhole = game->getSceneManager()->addBillboardSceneNode(0, irr::core::dimension2df(80.0f,100.0f), position );
	
	// Setting materials
	_wormhole->setMaterialFlag(video::EMF_LIGHTING, false);
	_wormhole->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	_wormhole->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	// Setting Texture
	const char* filePath = "../assets/Textures/Wormholes/WormHole.png";
	_wormhole->setMaterialTexture(0, game->driver->getTexture( filePath ));
}

// Needs setPosition because else te node will not get moved
void WormHole::setPosition(irr::core::vector3df &newPos){
	this->transform->position = &newPos;
	_wormhole->setPosition( newPos );
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
