#ifndef ENTITY_SHIP
#define ENTITY_SHIP

#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"
#include "Irrlicht\irrlicht.h"

#include "Stations\Station.h"
#include "Engine/Entity.h"
#include "Player.h"

#define STATION_TYPE Station :: StationType
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
	IGUIEnvironment *env;
	IGUIStaticText *shipHealth;
	IGUIStaticText *defenceStationHealth;
	IGUIStaticText *helmStationHealth;
	IGUIStaticText *navigationStationHealth;
	IGUIStaticText *powerStationHealth;
	IGUIStaticText *weaponStationHealth;


	int _shipHealth;
	bool _shipDestroyed;

	void update();
	void updateShipHealth();
	void draw();
	
	Ship(Composite * parent);
	virtual ~Ship(void);

	Station *GetStation( Station :: StationType );

	int getShipHealth();
	bool getShipDestroyed();
};
#endif