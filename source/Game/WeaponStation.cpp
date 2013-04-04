#include "WeaponStation.h"
#include "Engine\Game.h"
#include "Ship.h"

WeaponStation::WeaponStation(Composite* parent) : Entity(parent)
{
	cameramover = new WeaponCameraMover(this);
	addComponent(cameramover);
	this->_stationTexture = Game::driver->getTexture("../../assets/Textures/Stations/weapon station.png");
	Game::driver->makeColorKeyTexture(this->_stationTexture, position2d<s32>(0, 0));

	_nrOfBullets = 10;
	((Ship*)this->parent)->ammo = new Bullet[_nrOfBullets];
	_bulletNr = 0;
	_shootingInterval = 0;

	for (int i = 0; i < _nrOfBullets; i++)
	{
		Game::getCurrentScene()->addComponent(&((Ship*)this->parent)->ammo[i]);
	}
}

WeaponStation::~WeaponStation()
{
	Entity::~Entity();
}

void WeaponStation::update()
{
	_shootingInterval++;
	if(_shootingInterval == 1000)
	{
		shoot();
		_shootingInterval = 0;
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

	((Ship*)this->parent)->ammo[_bulletNr].setState(Game::getCurrentScene(), start, end, 0.5f);
	_bulletNr++;
	if(_bulletNr >= 10)
	{
		_bulletNr = 0;
	}
}