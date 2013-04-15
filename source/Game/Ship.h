#ifndef ENTITY_SHIP
#define ENTITY_SHIP
#include "Thruster.h"
#include "Engine\Camera.h"
#include "ShipMover.h"
#include "net.h"

#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"

#include "Stations\Station.h"
#include "Engine/Entity.h"
#include "Engine\Input.h"

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
	Ship(Composite * parent, vector3df position, vector3df rotation);
	DefenceStation		*_defenceStation;
	HelmStation			*_helmStation;
	NavigationStation	*_navigationStation;
	PowerStation		*_powerStation;
	WeaponStation		*_weaponStation;
	
public:
	virtual ~Ship(void);

	void init(int station);
	void handleMessage(unsigned int message, void* data);

	Net* network;
	int stationnumber;
	Station* currentstation;
	Input* input;
	Camera* camera;


	Thruster* thrusters[3];


	int nrOfBullets;
	Bullet *ammo;
	int bulletNr;
	int shootingInterval;
	void setInertiaMatrix(float h, float w, float d, float m);
	matrix4 inertiaMatrix;
	Station *GetStation( Station :: StationType );	
};
#endif