#include "SectorTemplate.h"
#include "Messages.h"
#include "Skybox.h"

SectorTemplate::SectorTemplate(Composite* parent, Entity player, const io::path & skyBoxTexture, float boundryRadius) : Entity(parent) {
	// Creating Skybox
	_skybox = new Skybox(skyBoxTexture, this);
	
	// Setting the boundry
	_boundry = boundryRadius;

	// The player
	this->_player = &player;
}

void SectorTemplate::init(){
	addComponent( this->_skybox );
	addComponent( this->_player );
}

void SectorTemplate::update(){
	if( this->_player->position.getLength() > _boundry ){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}
}

void SectorTemplate::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorTemplate::~SectorTemplate() {
	Entity::~Entity();
}
