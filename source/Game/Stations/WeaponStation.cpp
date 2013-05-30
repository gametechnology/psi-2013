#include "WeaponStation.h"

using namespace irr;

#define ANGLESPEED = 1

WeaponStation::WeaponStation(Core* core, Interface* ui, Ship *ship) : Station(core, ui, ship)
{
	_stationType = ST_WEAPON;
	setStationDestroyed(false);
}

WeaponStation::~WeaponStation()
{
	Station::~Station();
}

void WeaponStation::init()
{
	_stationTexture = _core->getDriver()->getTexture("../assets/Textures/Stations/WeaponStation/weapon_station.png");
	_core->getDriver()->makeColorKeyTexture(_stationTexture, irr::core::vector2d<irr::s32>(0, 0));
	Station::init();
}

void WeaponStation::update()
{
	if(_core->getInput()->isKeyboardButtonDown(KEY_SPACE) && getPower()){
		_ship->fireLaser();
	}

	if (_core->getInput()->isKeyboardButtonDown(KEY_RIGHT) || _core->getInput()->isKeyboardButtonDown(KEY_KEY_D)){
		if(rotationOwn.Y <= 90)
			rotationOwn.Y++;}
	if (_core->getInput()->isKeyboardButtonDown(KEY_LEFT) || _core->getInput()->isKeyboardButtonDown(KEY_KEY_A)){
		if(rotationOwn.Y >= -90)
			rotationOwn.Y--;}
	if (_core->getInput()->isKeyboardButtonDown(KEY_UP) || _core->getInput()->isKeyboardButtonDown(KEY_KEY_W)){
		if(rotationOwn.X >= -90)
			rotationOwn.X--;}
	if (_core->getInput()->isKeyboardButtonDown(KEY_DOWN) || _core->getInput()->isKeyboardButtonDown(KEY_KEY_S)){
		if(rotationOwn.X <= 90)
			rotationOwn.X++;}

	_ship->setRotation(&(rotationForeign + rotationOwn));

	Station::update();
}

void WeaponStation::draw()
{
	_core->getDriver()->draw2DImage(_stationTexture,
		irr::core::vector2d<s32>(0, 0),
		irr::core::rect<s32>(0, 0, 1280, 720),
		0,
		irr::video::SColor(255, 255, 255, 255),
		true);

	Station::draw();
}

void WeaponStation::enable()
{
	rotationForeign	= *_ship->getRotation();
	_ship->help->setHelpText(L"Shoot: 'space'\ntodo: Exit station: 'Esc'");

	Station::enable();
}

void WeaponStation::disable()
{
	_ship->setRotation(&rotationForeign);
	Station::disable();
}