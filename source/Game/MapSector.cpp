#include "MapSector.h"
#include "Engine\Game.h"


MapSector::MapSector(Composite *parent,std::string name,typeSector type, float radius):Entity(parent)
{
	this->name = name;
	this->type = type;
	this->explored = false;
	this->radius = radius;

	switch(type){
		case EMPTY:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/empty.png");
			break;

		case ASTEROID:
			this->_mapSectorTexture = Game::driver->getTexture("../assets/Textures/MapSectors/asteroid.png");
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
	
	Game::driver->draw2DImage(this->_mapSectorTexture,
							rect<s32>(this->position.X - radius,this->position.Y - radius,this->position.X + radius,this->position.Y + radius),
							rect<s32>(0,0,_mapSectorTexture->getOriginalSize().Width,_mapSectorTexture->getOriginalSize().Height),
							0,
							0,
							true);

}
