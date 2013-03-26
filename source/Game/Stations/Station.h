#ifndef STATION_BASE
#define STATION_BASE
#pragma once

#include "..\Player.h"

#ifdef ENTITY_SHIP
#include "..\Ship.h"
#endif

class Ship;

class Station 
{

public:
	Station( Ship *ship );
	~Station( ) { }

	virtual void DoCameraShake() = 0;

	enum StationType
	{
		Power = 0,
		Defence = 1,
		Weapon = 2,
		Helm = 3,
		Navigation = 4
	};

	//StationType GetStationType();
	bool HasPlayer();
	bool SwitchTimePassed();
	bool IsStunned();

	bool HasPower();
	bool HasArmor();

	void Update(float time);		

protected:
	Ship *_ship;

	Player *_player;
	float _switchTime;
	float _playerOnStationTime;
	float _stunTimeLeft;
	
	StationType _stationType;
};
//#endif
#endif