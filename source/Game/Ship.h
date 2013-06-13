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
#include "HudHelpText.h"
#include "PlayerInfoScreen.h"
#include "ShipInterface.h"

#include "ShipHealthComponent.h"
#include "IShipListener.h"

class DefenceStation;
class HelmStation;
class NavigationStation;
class PowerStation;
class WeaponStation;

class Ship : public ShipInterface, public INetworkListener
{
public:
	HudHelpText* help;
	PlayerInfoScreen* playerInfoScreen;
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

	irr::gui::IGUIStaticText *pingGuiText;
	ShipHealthComponent* shipHealthComponent;

	bool _shipDestroyed;

	bool _sitOnStation;

	void onAdd();
	void init();

	void update();
	void draw();
	
	int getTeamId();

	void CheckChangeInput();

	Ship(vector3df position, vector3df rotation, int teamId);
	virtual ~Ship(void);

	Station*	GetStation(StationType);
	Thruster**	GetThrusters();
	matrix4* GetInertiaMatrix();
	int getShipHealth();
	bool getShipDestroyed();

	void SwitchToStation(StationType stationType);

	static ObjectPool<Laser>* laserPool;

	void fireLaser();
	void leaveStation(StationType station);
	
	void HandleNetworkMessage(NetworkPacket packet);

	void addIShipListener(IShipListener* listener);
	void removeIShipListener(IShipListener* listener);

	void notifyIShipListeners(ShipMessage message);

	void foundEnemyBase();
	void backAtOwnBase();

private:
	std::list<IShipListener*> listeners;

	Station				*_currentStation;
	Thruster			*_thrusters[4];
	matrix4				*_inertiaMatrix;

	int _teamId;

	stringw varToString(stringw str1, float var, stringw str2);
	stringw varToString(stringw str1, float var);
	bool _foundEnemyBase;
	bool _backAtOwnBase;

	void setInertiaMatrix(float h, float w, float d, float m);

	//delete
	int a;
};
#endif
