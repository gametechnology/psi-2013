#ifndef DEFENCE_STATION
#define DEFENCE_STATION
#pragma once

#include "Station.h"
#include "..\Ship.h"
#include <time.h>
#include <map>

typedef struct Stats;

class DefenceStation : public Station
{
private:
	struct Stats
	{
	public:
		Stats( )
		{
			this -> health	= 10;
			this ->	armor	= 10;
		}

		Stats( float health, float armor )
		{
			this -> health	= health;
			this -> armor	= armor;
		}

		float health;
		float armor;
		bool HasArmor( );
		bool IsStunned( );
	};
	map<Station :: StationType, DefenceStation :: Stats> *_stations;
	
public:
	DefenceStation( Ship* ship);
	~DefenceStation(void);
	
	void DoCameraShake();
	int GetDamage( Station :: StationType stationType );
	void Damage();

	Station *station;


protected:
	void Init( );
};

#endif