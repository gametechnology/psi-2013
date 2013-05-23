#include "WeaponStation.h"

WeaponStation::WeaponStation(Ship *ship) : Station(ship)
{
	_stationType = ST_WEAPON;
	setStationDestroyed(false);
}

WeaponStation::~WeaponStation()
{
	Station::~Station();
}

void WeaponStation::onAdd()
{
	Station::onAdd();
}

void WeaponStation::init()
{
	Station::init();

	_stationTexture = game->driver->getTexture("../assets/Textures/Stations/WeaponStation/weapon_station.png");
	game->driver->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));
}

void WeaponStation::update()
{
	Station::update();

	if(game->input->isKeyboardButtonPressed(KEY_SPACE) /* && weapon station has power */)
		_ship->fireLaser();
}

void WeaponStation::draw()
{
	Station::draw();

	game->driver->draw2DImage(_stationTexture,
		irr::core::vector2d<s32>(0, 0),
		irr::core::rect<s32>(0, 0, 1280, 720),
		0,
		irr::video::SColor(255, 255, 255, 255),
		true);
}

void WeaponStation::enable()
{
	Station::enable();
}

void WeaponStation::disable()
{
	Station::disable();
}
void WeaponStation::HandlePosition(NetworkPacket pack){

}