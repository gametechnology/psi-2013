#include "MapSector.h"
#include "Engine\Game.h"

MapSector::MapSector(std::string name,typeSector type, float radius) : Entity()
{
	this->name = name;
	this->type = type;
	this->explored = false;
	this->radius = radius;
	this->distToBlueBase = INT_MAX;
}

void MapSector::onAdd() {
	resetTexture();
}

MapSector::~MapSector(void)
{

}

void MapSector::resetTexture()
{
	switch(type){
		case EMPTY:
			this->_mapSectorTexture = game->driver->getTexture("../assets/Textures/MapSectors/empty.png");
			break;

		case ASTEROID:
			this->_mapSectorTexture = game->driver->getTexture("../assets/Textures/MapSectors/asteroid.png");
			break;

		case NEBULA:
			this->_mapSectorTexture = game->driver->getTexture("../assets/Textures/MapSectors/nebula.png");
			break;

		case HOME_BLUE:
			this->_mapSectorTexture = game->driver->getTexture("../assets/Textures/MapSectors/home_blue.png");
			break;
	
		case HOME_RED:
			this->_mapSectorTexture = game->driver->getTexture("../assets/Textures/MapSectors/home_red.png");
			break;
	
		case SOLAR:
			this->_mapSectorTexture = game->driver->getTexture("../assets/Textures/MapSectors/solar.png");
			break;
	
	}
	game->driver->makeColorKeyTexture(this->_mapSectorTexture, core::position2d<s32>(0, 0));
}

void MapSector::draw(){
	game->driver->draw2DImage(this->_mapSectorTexture,
		irr::core::rect<s32>((int)(this->transform->position->X - radius), (int)(this->transform->position->Y - radius), (int)(this->transform->position->X + radius), (int)(this->transform->position->Y + radius)),
		irr::core::rect<s32>(0, 0, _mapSectorTexture->getOriginalSize().Width, _mapSectorTexture->getOriginalSize().Height),
		0,
		0,
		true);
}
