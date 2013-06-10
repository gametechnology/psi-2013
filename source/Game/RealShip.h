#ifndef REALSHIP_H
#define REALSHIP_H

#include "Irrlicht\irrlicht.h"

#include "Engine/Entity.h"
#include "Engine/IrrlichtNode.h"

#include "NetworkInterface.h"

#include "Stations\Station.h"
#include "Stations\DefenceStation.h"
#include "Stations\HelmStation.h"
#include "Stations\NavigationStation.h"
#include "Stations\PowerStation.h"
#include "Stations\WeaponStation.h"


#include "Thruster.h"
//#include "ShipMover.h"
#include "Laser.h"
#include "ObjectPool.h"
#include "HudHelpText.h"

#include "Ship.h"

class DefenceStation;
class HelmStation;
class NavigationStation;
class PowerStation;
class WeaponStation;

class RealShip : public Ship, public INetworkListener
{
public:
	RealShip(vector3df position, vector3df rotation);
	virtual ~RealShip(void);

	HudHelpText* help;

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

	bool _shipDestroyed;
	bool _sitOnStation;

	void onAdd();
	void init();

	void update();
	void draw();

	void CheckChangeInput();

	Station*	GetStation(StationType);
	Thruster**	GetThrusters();

	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType);

	static ObjectPool<Laser>* laserPool;

	void fireLaser();
	
	void HandleNetworkMessage(NetworkPacket packet);

private:
	Station				*_currentStation;
	Thruster			*_thrusters[4];
	matrix4				*_inertiaMatrix;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);

	void setInertiaMatrix(float h, float w, float d, float m);
};
#endif