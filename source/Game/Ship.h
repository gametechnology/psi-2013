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
#include "Engine/IrrlichtNode.h"
#include "Player.h"
#include "Thruster.h"
#include "Engine\Camera.h"
#include "ShipMover.h"
#include "Laser.h"
#include "ObjectPool.h"

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

	//to test the ship health and station health
	irr::gui::IGUIEnvironment *env;
	irr::gui::IGUIStaticText *shipHealth;
	irr::gui::IGUIStaticText *defenceStationHealth;
	irr::gui::IGUIStaticText *helmStationHealth;
	irr::gui::IGUIStaticText *navigationStationHealth;
	irr::gui::IGUIStaticText *powerStationHealth;
	irr::gui::IGUIStaticText *weaponStationHealth;


	bool _shipDestroyed;

	bool _sitOnStation;

	void onAdd();
	void init();

	void update();
	void draw();

	void CheckChangeInput();

	Ship(vector3df position, vector3df rotation);
	virtual ~Ship(void);

	Station*	GetStation(StationType);
	Thruster**	GetThrusters();

	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType);

	static ObjectPool<Laser>* laserPool;

	void fireLaser();
private:

	Station				*_currentStation;
	Camera				*_camera;
	Thruster			*_thrusters[4];
	matrix4				*_inertiaMatrix;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);
};
#endif
