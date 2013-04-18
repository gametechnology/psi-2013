#ifndef STATION_BASE
#define STATION_BASE
#pragma once

#include "..\Player.h"
#include "../../../include/Engine/Component.h"
#include "../../../include/Engine/Game.h"
#include "Irrlicht/irrlicht.h"
#ifdef ENTITY_SHIP
#include "..\Ship.h"
#endif

#define STUN_TIME 4.0
class Ship;
	
enum StationType
{
	ST_POWER		= 0,
	ST_DEFENCE		= 1,
	ST_WEAPON		= 2,
	ST_HELM		= 3,
	ST_NAVIGATION	= 4
};

class Station : public Composite
{
public:
	Station( Ship *ship, int startHealth );
	Station( Ship *ship );
	virtual ~Station(void);

	virtual void DoCameraShake() = 0;

	StationType GetStationType();
	bool HasPlayer();
	bool SwitchTimePassed();
	bool IsStunned();

	bool HasPower();
	bool HasArmor();

	bool getStationDestroyed();
	void setStationDestroyed(bool _destroyed);

	int getHealth();
	void updateHealth();
	void increaseHealth(int health);
	void decreaseHealth(int health);
	void repairStation(int health);

	void update();

	virtual void OnDamage( );

protected:
	video::IVideoDriver *driver;

	Ship	*_ship;
	Player	*_player;

	time_t *_switchTime;			//the time that the player switched to this station
	time_t *_playerOnStationTime;	//the time that the player has spent on this station (since he switched)
	time_t *_stunTime;				//if a station fot stunned, the time it happened will be stored here.
	
	StationType _stationType;

private:
	int _tempTimer;
	int _totalHealth;
	int _health;
	bool _stationDestroyed;

public:
	void Initialize( );
};
#endif