#include "WeaponStation.h"
#include "Engine\Game.h"
#include "Ship.h"

WeaponStation::WeaponStation(Composite* parent) : Entity(parent)
{
	cameramover = new WeaponCameraMover(this);
	addComponent(cameramover);
	this->_stationTexture = Game::driver->getTexture("../assets/Textures/Stations/weapon station.png");
	Game::driver->makeColorKeyTexture(this->_stationTexture, position2d<s32>(0, 0));
}

WeaponStation::~WeaponStation()
{
	Entity::~Entity();
}

void WeaponStation::update()
{
	((Ship*)this->parent)->shootingInterval++;
	if(((Ship*)this->parent)->shootingInterval == 1000)
	{
		shoot();
		((Ship*)this->parent)->shootingInterval = 0;
	}
	cameramover->update();
	Entity::update();
}

void WeaponStation::draw()
{
	Game::driver->draw2DImage(this->_stationTexture,
		position2d<s32>(0,0),
		rect<s32>(0,0,1280,720),
		0,
		SColor(255,255,255,255),
		true);

	Entity::draw();
}

void WeaponStation::shoot()
{
	core::vector3df start = Game::device->getSceneManager()->getActiveCamera()->getPosition();
	core::vector3df end = (Game::device->getSceneManager()->getActiveCamera()->getTarget() - start);

	((Ship*)this->parent)->ammo[((Ship*)this->parent)->bulletNr].setState(Game::getCurrentScene(), start, end, 0.5f);
	((Ship*)this->parent)->bulletNr++;
	if(((Ship*)this->parent)->bulletNr >= 10)
	{
		((Ship*)this->parent)->bulletNr = 0;
	}
}