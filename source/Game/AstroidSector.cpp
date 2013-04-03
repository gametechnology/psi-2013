#include "AstroidSector.h"
#include "Messages.h"
#include "Skybox.h"

void AstroidSector::init(){
	addComponent( this->_skybox );
	addComponent( this->_player );
}

void AstroidSector::update(){
	if( this->_player->position.getLength() > _boundry ){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}
}

void AstroidSector::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

AstroidSector::~AstroidSector() {
	Entity::~Entity();
}
