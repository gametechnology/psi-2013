#ifndef DEFENCE_STATION
#define DEFENCE_STATION
#pragma once

#include "Station.h"
#include "..\Ship.h"
#include <time.h>
#include <map>

class DefenceStation : public Station
{
private:
	struct DefenceStats
	{
	public:
		DefenceStats( )
		{
			this -> health	= 10;
			this ->	armor	= 10;
		}

		DefenceStats( float health, float armor )
		{
			this -> health	= health;
			this -> armor	= armor;
		}

		float health;
		float armor;
		bool HasArmor( );
		bool IsStunned( );
	};
	map<StationType, DefenceStation :: DefenceStats> *_stations;
	
public:
	DefenceStation( Ship* ship);
	~DefenceStation(void);
	
	void DoCameraShake();
	int GetDamage(StationType stationType );
	void Damage();
	void SubscribeStation( Station *s );

	Station *station;
};

#endif