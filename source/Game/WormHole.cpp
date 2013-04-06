#include "WormHole.h"
#include "Engine/Game.h"

WormHole::WormHole(Composite* parent, unsigned int id, irr::core::vector3df position) : Entity(parent) {
	const char* filePath = "../assets/Textures/Wormholes/WormHole.png";
	this->id = id;
	this->position = position;
	_wormhole = Game::getSceneManager()->addBillboardSceneNode(0, irr::core::dimension2df(30.0f,30.0f) );
	_wormhole->setMaterialFlag(EMF_LIGHTING, false);
	_wormhole->setMaterialFlag(EMF_FOG_ENABLE, true);
	_wormhole->setMaterialType(EMT_TRANSPARENT_ALPHA_CHANNEL);
	_wormhole->setMaterialTexture(0, Game::driver->getTexture( filePath ));
	//this->angularVelocity = irr::core::vector3df(2,0,0);
}

void WormHole::update(){
	Entity::update();
}

void WormHole::handleMessage(unsigned int message, void* data) {
	delete data;
}

WormHole::~WormHole() {
	Entity::~Entity();
}
