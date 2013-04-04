#include "SectorTemplate.h"
#include "Engine/Camera.h"
#include "Skybox.h"
#include "SectorManager.h"


SectorTemplate::SectorTemplate(SectorManager* sectormanager, const io::path & skyBoxTexture, float boundryRadius, unsigned int amountWormHoles) : Scene() {
	//setting sector Manager
	_sectormanager = sectormanager;
	// Creating Skybox
	_skybox = new Skybox(skyBoxTexture, this);
	
	// Setting the boundry
	_boundry = boundryRadius;

	// The player
	this->_player = new Camera( this->parent );
	Game::getSceneManager()->addCameraSceneNodeFPS();
	// Creating wormholes
	createWormHoles( amountWormHoles );
	
	//init();
}

void SectorTemplate::init(){
	addComponent( this->_skybox );
	addComponent( this->_player );
}

void SectorTemplate::createWormHoles( unsigned int amountOfWormHoles ){
			printf("[SectorTemplate] -=*[Begin of Create WormHole]*=- \n");
	for(unsigned int i = 0; i < amountOfWormHoles; i++){
		wormHole = new WormHole(this->parent, i, irr::core::vector3df( rand() % int(_boundry*2) - int(_boundry), rand() % int(_boundry*2) - int(_boundry), rand() % int(_boundry*2) - int(_boundry) ) );
		this->_wormHoles.push_back( wormHole );
		addComponent(wormHole );
	}
			printf("[SectorTemplate] -=*[End of Create WormHole]*=- \n");
}

void SectorTemplate::update(){
	if( this->_player->position.getLength() > _boundry ){
		this->_player->handleMessage(OUT_OF_BOUNDS, NULL);
	}
	
	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = _wormHoles[i]->position - this->_player->position;
		if( deltaPos.getLength() < 10 ){			
			printf("[SectorTemplate]i = %i &i = %i \n",i,&i);
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
