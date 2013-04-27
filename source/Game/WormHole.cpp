#include "WormHole.h"
#include "Engine/Game.h"

WormHole::WormHole(unsigned int id) : Entity() {
	// Setting id and position
	this->id = id;
}

void WormHole::onAdd() {
	// Creating a 2d Node in 3d space that always looks straight to the camera, irlicht functionalitie.
	_wormhole = scene->getIrrlichtSceneManager()->addBillboardSceneNode(0, irr::core::dimension2df(80.0f,100.0f), *transform->position );
	
	// Setting materials
	_wormhole->setMaterialFlag(video::EMF_LIGHTING, false);
	_wormhole->setMaterialFlag(video::EMF_FOG_ENABLE, true);
	_wormhole->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	// Setting Texture
	const char* filePath = "../assets/Textures/Wormholes/WormHole.png";
	_wormhole->setMaterialTexture(0, game->driver->getTexture( filePath ));
}

// Added update for possible annimations
void WormHole::update(){
	_wormhole->setPosition(*this->transform->position);
	Entity::update();
}

void WormHole::handleMessage(unsigned int message, void* data) {
	delete data;
}

WormHole::~WormHole() {
	_wormhole->drop();
	//delete _wormhole;
	Entity::~Entity();
}
