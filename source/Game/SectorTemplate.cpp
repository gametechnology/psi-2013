#include "SectorTemplate.h"
#include "Messages.h"
#include "Skybox.h"

SectorTemplate::SectorTemplate(Composite* parent, Entity player, const io::path & skyBoxTexture, float boundryRadius) : Entity(parent) {
	// Creating Skybox
	Skybox* skybox = new Skybox(skyBoxTexture, this);
	addComponent( skybox );
	
	// Setting the boundry
	this->boundry.setLength( boundryRadius );

	// Setting the player
	this->playerPosition = &player.position;
}

void SectorTemplate::update(){
	this->playerPosition;
}

void SectorTemplate::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorTemplate::~SectorTemplate() {
	Entity::~Entity();
}
