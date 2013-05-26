#include "WeaponStation.h"

#define ANGLESPEED = 1

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

	if(game->input->isKeyboardButtonPressed(KEY_SPACE)){
		_ship->fireLaser();
		NetworkPacket firepacket = NetworkPacket(PacketType::CLIENT_FIRE_LASER);
		firepacket << *_ship->transform->rotation;
		if(!Network::GetInstance()->IsServer())
			Network::GetInstance()->SendPacket(firepacket, true);
	}

	if (game->input->isKeyboardButtonDown(KEY_RIGHT) || game->input->isKeyboardButtonDown(KEY_KEY_D)){
		if(rotationOwn.Y <= 90)
			rotationOwn.Y++;}
	if (game->input->isKeyboardButtonDown(KEY_LEFT) || game->input->isKeyboardButtonDown(KEY_KEY_A)){
		if(rotationOwn.Y >= -90)
			rotationOwn.Y--;}
	if (game->input->isKeyboardButtonDown(KEY_UP) || game->input->isKeyboardButtonDown(KEY_KEY_W)){
		if(rotationOwn.X >= -90)
			rotationOwn.X--;}
	if (game->input->isKeyboardButtonDown(KEY_DOWN) || game->input->isKeyboardButtonDown(KEY_KEY_S)){
		if(rotationOwn.X <= 90)
			rotationOwn.X++;}

	*_ship->transform->rotation = rotationForeign + rotationOwn;
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
	
	rotationForeign	= *_ship->transform->rotation;
	((Ship*)parent)->help->setHelpText(L"Shoot: 'space'\ntodo: Exit station: 'Esc'");

	Station::enable();
}

void WeaponStation::disable()
{
	_ship->transform->rotation->set( rotationForeign);
	Station::disable();
}