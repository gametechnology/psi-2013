#include "SectorTemplate.h"
#include "Engine/Camera.h"
#include "Skybox.h"
#include "SectorManager.h"

// Constructor
SectorTemplate::SectorTemplate(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : Scene() {
	//setting sector Manager
	_sectormanager = sectormanager;
	// Creating Skybox
	_skybox = new Skybox(skyBoxTexture, this);
	// Adding mist
	_fog = new Mist(this);
	// Setting the boundry
	_boundry = boundryRadius;

	// The player
	this->_player = new Camera( this->parent );
	Game::getSceneManager()->addCameraSceneNodeFPS();
	// Creating wormholes
	createWormHoles( amountWormHoles );
	
	init();
}
//This function isn't being overriden so it needs to be called in constructor
void SectorTemplate::init(){
	addComponent( this->_skybox );
	//addComponent( this->_player );
	addComponent( this->_fog );
}

void SectorTemplate::createWormHoles( unsigned int amountOfWormHoles ){
			printf("[SectorTemplate] -=*[Begin of Create WormHole]*=- \n");
	for(unsigned int i = 0; i < amountOfWormHoles; i++){
		// Creating a wormhole and giving it a random place
		wormHole = new WormHole(this->parent, i, irr::core::vector3df( rand() % int(_boundry*2) - int(_boundry), rand() % int(_boundry*2) - int(_boundry), rand() % int(_boundry*2) - int(_boundry) ) );
		// Making sure that the wormhole isn't spawned between 0% and 80% from the zero point to the radius of the sector
		wormHole->position.setLength(rand() % int(_boundry* 0.2) + int(_boundry* 0.8));
		// Pushing to the wormhole list
		this->_wormHoles.push_back( wormHole );
		addComponent(wormHole);
	}
			printf("[SectorTemplate] -=*[End of Create WormHole]*=- \n");
}

void SectorTemplate::update(){
	// Checking if the player isn't going out side of the radius of the sector
	if( this->_player->position.getLength() > _boundry ){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}
	
	// Checking for collision with a wormhole
	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = _wormHoles[i]->position - this->_player->position;
		if( deltaPos.getLength() < 10 ){			
			_sectormanager->handleMessage(NEXT_SECTOR,(void*)i );
			break;
		}
	}
	Scene::update();
}

void SectorTemplate::handleMessage(unsigned int message, void* data) {
	
	delete data;
}

SectorTemplate::~SectorTemplate() {
	Scene::~Scene();
}
