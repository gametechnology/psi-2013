#include "WeaponStation.h"
#include "Engine\Game.h"
#include "Ship.h"
WeaponStation::WeaponStation(Composite* parent) : Entity(parent)
{
	cameramover = new WeaponCameraMover(this);
	
	this->_stationTexture = Game::driver->getTexture("../../assets/Textures/Stations/weapon station.png");
	Game::driver->makeColorKeyTexture(this->_stationTexture, position2d<s32>(0, 0));
}

WeaponStation::~WeaponStation()
{
	Entity::~Entity();
}

void WeaponStation::draw()
{
	Game::driver->draw2DImage(this->_stationTexture,
		position2d<s32>(0,0),
		rect<s32>(0,0,1280,720),
		0,
		SColor(255,255,255,255),
		true);
}