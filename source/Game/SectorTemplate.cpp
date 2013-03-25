#include "SectorTemplate.h"
#include "Messages.h"
#include "Skybox.h"

SectorTemplate::SectorTemplate(Composite* parent, Entity player, const io::path & skyBoxTexture, float boundryRadius) : Entity(parent) {
	// Creating Skybox
	Skybox* skybox = new Skybox(skyBoxTexture, this);
	addComponent( skybox );
	
	// Setting the boundry
	this->_boundry->setLength( boundryRadius );

	// Setting the player
	this->_playerPosition = &player.position;

	// The player
	this->_player = &player;
}

void SectorTemplate::update(){
	if(this->_playerPosition->getLength() > this->_boundry->getLength()){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}
}

void SectorTemplate::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorTemplate::~SectorTemplate() {
	Entity::~Entity();
}
