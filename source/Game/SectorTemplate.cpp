#include "SectorTemplate.h"
#include "Engine/Camera.h"
#include "Skybox.h"

SectorTemplate::SectorTemplate(Composite* parent, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : Entity(parent) {
	// Creating Skybox
	_skybox = new Skybox(skyBoxTexture, this);
	
	// Setting the boundry
	_boundry = boundryRadius;

	// The player
	this->_player = new Camera( this->parent );

	// Creating wormholes
	createWormHoles( amountWormHoles );
	
	init();
}

void SectorTemplate::init(){
	addComponent( this->_skybox );
	addComponent( this->_player );
}

void SectorTemplate::createWormHoles( unsigned int amountOfWormHoles ){
	for(unsigned int i = 0; i < amountOfWormHoles; i++){
		wormHole = new WormHole(this->parent, i, irr::core::vector3df( rand() % int(_boundry*2) - int(_boundry), rand() % int(_boundry*2) - int(_boundry), rand() % int(_boundry*2) - int(_boundry) ) );
		this->_wormHoles.push_back( wormHole );
		addComponent(wormHole );
	}
}

void SectorTemplate::update(){
	if( this->_player->position.getLength() > _boundry ){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}

	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = this->_player->position - _wormHoles[i]->position;
		if( deltaPos.getLength() < 10 ){
			Game::getCurrentScene()->handleMessage(NEXT_SECTOR, new int(i));
		}
	}
}

void SectorTemplate::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorTemplate::~SectorTemplate() {
	Entity::~Entity();
}
