#include "HelmStation.h"
#include "Engine\Game.h"

HelmStation::HelmStation(Composite* parent) : Entity(parent)
{
	this->_stationTexture = Game::driver->getTexture("../../assets/Textures/Stations/weapon station.png");
	Game::driver->makeColorKeyTexture(this->_stationTexture, position2d<s32>(0, 0));
}

HelmStation::~HelmStation()
{
	Entity::~Entity();
}

void HelmStation::draw()
{
	Game::driver->draw2DImage(this->_stationTexture,
		position2d<s32>(0,0),
		rect<s32>(0,0,1280,720),
		0,
		SColor(255,255,255,255),
		true);
}