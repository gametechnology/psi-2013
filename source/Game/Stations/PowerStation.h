#ifndef POWER_STATION
#define POWER_STATION

#include "Station.h"
#include "..\Ship.h"
#include <time.h>
#include <map>
#include <iostream>

typedef struct PowerUsage;

#define POWER_MAX	100
#define BOOST_TIME	10

class PowerStation : public Station 
{
private:
	struct PowerUsage
	{
	public:
		PowerUsage( ) { powerCurrent = 0; };
		PowerUsage( int powerCurrent );
		//this is the current powerlevel of the given station
		int powerCurrent;
	};

	time_t _timeOfLastBoost;
	float _powerMax;	//starts at 100
	map<Station :: StationType, PowerUsage> *_stationsPowerUsage;

	//the pool that holds the total available power, this is initially 100% power.
	int _powerPool;
	//this is an integer holding the currently used power supply.
	int _powerUsed;

	//checks if the new value can be matched (cannot be lower than 0 or higher than the total energy in our pool) and then updates the value of the station's energy pool.
	void UpdateStationPower( Station :: StationType, int newValue );

public:
	PowerStation(Ship* ship);
	~PowerStation(void);
	bool IsPoolEmpty( );

	//shakes the camera whenever the station is hurt (aaaahh)
	void DoCameraShake( );

	//gets the power for a given station
	int GetPower(Station::StationType stationType);

protected:
	void Init( );
};

#endif