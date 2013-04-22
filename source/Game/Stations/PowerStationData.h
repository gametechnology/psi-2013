#ifndef GUI_STATION_DATA
#define GUI_STATION_DATA

#include <map>
#include "..\..\..\include\Irrlicht\irrlicht.h"
#include "Station.h"
#include <iostream>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#define MAX_INT(a, b) a > b ? a : b
#define MIN_INT(a, b) a < b ? a : b
#define POWER_MAX	100

class PowerStationData
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
	
	map<StationType, PowerUsage> *_stationsPowerUsage;
	time_t _timeOfLastBoost;	
	int _powerUsed;

public:
	PowerStationData( );

	int powerPool;
	int selectedStation;

	IGUIStaticText	*powerPoolText;
	IGUIStaticText	*stationSelectedText;
	IGUIStaticText	*helmStatus;
	IGUIStaticText	*defenceStatus;
	IGUIStaticText	*weaponStatus;
	IGUIStaticText	*navigationStatus;
	IGUIScrollBar	*scrollBar;
		
	s32			counter;
	IGUIListBox	*listbox;

	void SubscribeStation( Station *s );
	void UpdatePowerUsage(StationType s, int newValue );
	int GetPower(StationType stationType );
};
#endif