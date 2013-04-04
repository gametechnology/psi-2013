#ifndef ENTITY_SHIP
#define ENTITY_SHIP

#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"

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
	
public:
	Ship(Composite * parent);
	Ship( );
	virtual ~Ship(void);

	Station *GetStation( Station :: StationType );	
};
#endif