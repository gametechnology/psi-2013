#include "MapSector.h"

using namespace irr;
using namespace irr::core;

MapSector::MapSector(Core* core, std::string name,typeSector type, float radius) : GameObject()
{
	_core = core;
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
			this->_mapSectorTexture = _core->getDriver()->getTexture("../assets/Textures/MapSectors/empty.png");
			break;

		case ASTEROID:
			this->_mapSectorTexture = _core->getDriver()->getTexture("../assets/Textures/MapSectors/asteroid.png");
			break;

		case NEBULA:
			this->_mapSectorTexture = _core->getDriver()->getTexture("../assets/Textures/MapSectors/nebula.png");
			break;

		case HOME_BLUE:
			this->_mapSectorTexture = _core->getDriver()->getTexture("../assets/Textures/MapSectors/home_blue.png");
			break;
	
		case HOME_RED:
			this->_mapSectorTexture = _core->getDriver()->getTexture("../assets/Textures/MapSectors/home_red.png");
			break;
	
		case SOLAR:
			this->_mapSectorTexture = _core->getDriver()->getTexture("../assets/Textures/MapSectors/solar.png");
			break;
	
	}
	_core->getDriver()->makeColorKeyTexture(this->_mapSectorTexture, position2d<s32>(0, 0));
}

void MapSector::draw(){
	_core->getDriver()->draw2DImage(this->_mapSectorTexture,
		rect<s32>((int)(_position->X - radius), (int)(_position->Y - radius), (int)(_position->X + radius), (int)(_position->Y + radius)),
		rect<s32>(0, 0, _mapSectorTexture->getOriginalSize().Width, _mapSectorTexture->getOriginalSize().Height),
		0,
		0,
		true);
}
