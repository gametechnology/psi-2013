#ifndef STATION
#define STATION

#include "..\Ship.h"

class Station {

public:
	Station(Ship *ship);
	~Station();

	virtual void DoCameraShake() = 0;

	enum StationType
	{
		Power = 0,
		Defence = 1,
		Weapon = 2,
		Helm = 3,
		Navigation = 4
	};

	Station::StationType GetStationType();
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
	
	Station::StationType _stationType;
};

#endif

