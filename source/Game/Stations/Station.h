#ifndef STATION_BASE
#define STATION_BASE
#pragma once

#include "..\Player.h"
#include "../../../include/Engine/Component.h"

#ifdef ENTITY_SHIP
#include "..\Ship.h"
#endif

#define STUN_TIME 4.0
class Ship;

class Station : public Component
{

public:
	Station( Ship *ship );
	~Station( ) { }

	virtual void DoCameraShake() = 0;

	enum StationType
	{
		Power		= 0,
		Defence		= 1,
		Weapon		= 2,
		Helm		= 3,
		Navigation	= 4
	};

	StationType GetStationType();
	bool HasPlayer();
	bool SwitchTimePassed();
	bool IsStunned();

	bool HasPower();
	bool HasArmor();

	void Update(float time);

	virtual void OnDamage( );

protected:
	Ship	*_ship;
	Player	*_player;

	time_t *_switchTime;				//the time that the player switched to this station
	time_t *_playerOnStationTime;	//the time that the player has spent on this station (since he switched)
	time_t *_stunTime;				//if a station fot stunned, the time it happened will be stored here.
	
	StationType _stationType;

public:
	void Initialize( );
};
//#endif
#endif