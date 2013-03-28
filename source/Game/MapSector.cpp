#include "MapSector.h"
#include "Engine\Game.h"


MapSector::MapSector(Composite *parent,std::string name,typeSector type):Entity(parent)
{
	this->connections = new std::list<MapSector*>();
	this->name = name;
	this->type = type;
	this->explored = false;

	switch(type){
		case EMPTY:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/empty.png");
			break;

		case ASTEROID:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/asteroids.png");
			break;

		case NEBULA:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/nebula.png");
			break;

		case HOME_BLUE:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/home_blue.png");
			break;
	
		case HOME_RED:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/home_red.png");
			break;
	
		case SOLAR:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/solar.png");
			break;
	
	}

	Game::driver->makeColorKeyTexture(this->_mapSectorTexture, position2d<s32>(0, 0));

}


MapSector::~MapSector(void)
{
}


void MapSector::draw(){
	
	Game::driver->draw2DImage(
							this->_mapSectorTexture,
							position2d<s32>(this->position.X,this->position.Y),
							rect<s32>(0,0,52,54),
							0,
							SColor(255,255,255,255),
							true);

}
