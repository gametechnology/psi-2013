#ifndef STATION_BASE
#define STATION_BASE
#pragma once

#include "../HudComposite.h"
#include "../Player.h"
#include "../../../include/Engine/Entity.h"
#include "../../../include/Engine/Component.h"
#include "../../../include/Engine/Game.h"
#include "Irrlicht/irrlicht.h"


#ifdef ENTITY_SHIP
#include "../Ship.h"
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

class Station : public Entity
{
public:
	Station( Ship *ship, int startHealth );
	Station( Ship *ship );
	virtual ~Station(void);
	void Initialize( );
	virtual void DoCameraShake() = 0;

	StationType GetStationType();
	bool HasPlayer();
	bool SwitchTimePassed();
	bool IsStunned();

	bool HasPower();
	bool HasArmor();

	std::string helpTextString;

	bool getStationDestroyed();
	void setStationDestroyed(bool _destroyed);

	int getHealth();
	void updateHealth();
	void increaseHealth(int health);
	void decreaseHealth(int health);
	void repairStation(int health);

	virtual void onAdd();
	virtual void init();
	virtual void update();
	
	virtual void OnDamage( );
	virtual void OnEnabled() = 0;
	virtual void OnDisabled() = 0;
	
	HudComposite* hud;

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
	// Energy testing variable for hud.
	int energy;
	// End energy testing variable for hud.
	int _health;
	bool _stationDestroyed;
};
#endif