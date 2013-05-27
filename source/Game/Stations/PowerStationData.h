#ifndef GUI_STATION_DATA
#define GUI_STATION_DATA

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
	
	
	irr::core::map<StationType, Station*> *_stationsPowerUsage;
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
	void UpdatePowerUsage(StationType s, int newValue, bool sentByServer );
	int GetPower(StationType stationType );
};
#endif