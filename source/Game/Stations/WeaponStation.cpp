#pragma once
#include "WeaponStation.h"
#include <iostream>

WeaponStation::WeaponStation(Ship *ship) : Station(ship)
{
	stationType = ST_WEAPON;
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

	_stationTexture = game->driver->getTexture("../assets/Textures/Stations/WeaponStation/weaponstation.png");
	game->driver->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));
}

void WeaponStation::update()
{
	Station::update();

	if(game->input->isKeyboardButtonPressed(KEY_SPACE))
		std::cout << "FIRE!!" << std::endl;
}

void WeaponStation::draw()
{
	game->driver->draw2DImage(_stationTexture, 
		irr::core::vector2d<s32>(0, 0), 
		rect<s32>(0,0,1280,720),
		0,
		SColor(255,255,255,255),
		true);

	Station::draw();
}

void WeaponStation::enable()
{
	Station::enable();
}

void WeaponStation::disable()
{
	Station::disable();
}

