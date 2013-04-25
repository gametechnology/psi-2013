#ifndef ENTITY_SHIP
#define ENTITY_SHIP
#pragma once

#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"
#include "Irrlicht\irrlicht.h"

#include "Stations\Station.h"
#include "Engine/Entity.h"
#include "Player.h"
#include "Engine/Input.h"

class DefenceStation;
class HelmStation;
class NavigationStation;
class PowerStation;
class WeaponStation;

class Ship : public Entity
{
public:
	//Player *players;
	DefenceStation		*_defenceStation;
	HelmStation			*_helmStation;
	NavigationStation	*_navigationStation;
	PowerStation		*_powerStation;
	WeaponStation		*_weaponStation;

	Input				*_input;

	//to test the ship health and station health
	irr::gui::IGUIEnvironment *env;
	irr::gui::IGUIStaticText *shipHealth;
	irr::gui::IGUIStaticText *defenceStationHealth;
	irr::gui::IGUIStaticText *helmStationHealth;
	irr::gui::IGUIStaticText *navigationStationHealth;
	irr::gui::IGUIStaticText *powerStationHealth;
	irr::gui::IGUIStaticText *weaponStationHealth;

	int _shipHealth;
	bool _shipDestroyed;

	bool _sitOnStation;

	void update();
	void updateShipHealth();
	void draw();

	void CheckChangeInput();

	Ship(Composite * parent, vector3df position, vector3df orientation);
	virtual ~Ship(void);

	Station *GetStation(StationType );	

	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType);
private:

	Station *_currentStation;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);
};
#endif