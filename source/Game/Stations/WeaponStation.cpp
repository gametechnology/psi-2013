#include "WeaponStation.h"

#define ANGLESPEED 3
#define MOUSE_ACTIVE_X 400
#define MOUSE_ACTIVE_Y 300
#define SCREEN_X 1280
#define SCREEN_Y 720

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

	if((game->input->isKeyboardButtonPressed(KEY_SPACE) || game->input->isMouseButtonPressed(LEFT_MB)) && getPower()){
		_ship->fireLaser();
	}

	if (game->input->isKeyboardButtonDown(KEY_RIGHT) || game->input->isKeyboardButtonDown(KEY_KEY_D)){
		if(rotationOwn.Y <= 90)
			rotationOwn.Y += ANGLESPEED;}
	if (game->input->isKeyboardButtonDown(KEY_LEFT) || game->input->isKeyboardButtonDown(KEY_KEY_A)){
		if(rotationOwn.Y >= -90)
			rotationOwn.Y -= ANGLESPEED;}
	if (game->input->isKeyboardButtonDown(KEY_UP) || game->input->isKeyboardButtonDown(KEY_KEY_W)){
		if(rotationOwn.X >= -90)
			rotationOwn.X -= ANGLESPEED;}
	if (game->input->isKeyboardButtonDown(KEY_DOWN) || game->input->isKeyboardButtonDown(KEY_KEY_S)){
		if(rotationOwn.X <= 90)
			rotationOwn.X += ANGLESPEED;}

	if(game->input->getMouseX() < MOUSE_ACTIVE_X){
		if(rotationOwn.Y >= -90)
			rotationOwn.Y -= ANGLESPEED;}
	if(game->input->getMouseX() > SCREEN_X - MOUSE_ACTIVE_X){
		if(rotationOwn.Y <= 90)
			rotationOwn.Y += ANGLESPEED;}
	if(game->input->getMouseY() < MOUSE_ACTIVE_Y){
		if(rotationOwn.X >= -90)
			rotationOwn.X -= ANGLESPEED;}
	if(game->input->getMouseY() > SCREEN_Y - MOUSE_ACTIVE_Y){
		if(rotationOwn.X <= 90)
			rotationOwn.X += ANGLESPEED;}

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
	((Ship*)parent)->help->setHelpText(L"Shoot: 'space'\nExit station: 'Esc'");

	Station::enable();
}

void WeaponStation::disable()
{
	_ship->transform->rotation->set( rotationForeign);
	Station::disable();
}