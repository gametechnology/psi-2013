#include "SectorTemplate.h"
#include "Engine/Camera.h"
#include "Skybox.h"
#include "SectorManager.h"
#include "Ship.h"

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
	
	_enemyManager = new EnemyManager();
	// The player
	//Get the player/Ship via Sectormanager
	//_sectormanager->getShip()
	_ship = new Ship();
	this->_player = new Camera( _ship, vector3df(0, 20, -10) ); //TODO: Make the camera work correctly according to station
	//this->_camera = Game::getSceneManager()->addCameraSceneNodeFPS();
	// Creating wormholes
	createWormHoles( amountWormHoles );
	
	init();
}
//This function isn't being overriden so it needs to be called in constructor
void SectorTemplate::init(){
	addChild(_enemyManager);
	addChild( this->_skybox );
	//addComponent( this->_player );
	addChild(_ship);
	addChild( this->_fog );
}

void SectorTemplate::createWormHoles( unsigned int amountOfWormHoles ){
			printf("[SectorTemplate] -=*[Begin of Create WormHole]*=- \n");
			printf("[SectorTemplate] -=*[Amount of wormholes %i]*=- \n", amountOfWormHoles);
	for(unsigned int i = 0; i < amountOfWormHoles; i++){
		// Calculating the pos in the sector
		irr::core::vector3df wormHolePos((float)(rand() % int(_boundry*2) - int(_boundry)), (float)(rand() % int(_boundry*2) - int(_boundry)), (float)(rand() % int(_boundry*2) - int(_boundry)));
		// Making sure that the wormhole isn't spawned between 0% and 80% from the zero point to the radius of the sector
		wormHolePos.setLength((float)(rand() % int(_boundry* 0.2) + int(_boundry* 0.8)));
		// Creating a wormhole and giving it the pos we just calculated
		wormHole = new WormHole(this->parent, i, wormHolePos );
		// Pushing to the wormhole list
		this->_wormHoles.push_back( wormHole );
		addChild(wormHole);
	}
	int size = _wormHoles.size();
			printf("[SectorTemplate] -=*[Size array %i ]*=- \n" , size);
			printf("[SectorTemplate] -=*[End of Create WormHole]*=- \n");
}

void SectorTemplate::update(){
	/* Original when player is done
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
	*/

	// Placeholder because there is no player yet
	/*To use Fps camera:
	replace:
	this->_ship->position
	with
	this->_camera->getPosition()*/
	if( this->_ship->transform->position->getLength() > _boundry ){
		printf("OUT OF BOUNDS!");
	}
	for(unsigned int i = 0; i < this->_wormHoles.size(); i++){
		irr::core::vector3df deltaPos = *_wormHoles[i]->transform->position - *this->_ship->transform->position;
		float collisionRadius = 50;
		if( deltaPos.getLength() < collisionRadius ){			
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
