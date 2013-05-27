#ifndef GUI_STATION_DATA
#define GUI_STATION_DATA

#include <Irrlicht\irrlicht.h>
#include "Station.h"
#include <iostream>

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

	irr::gui::IGUIStaticText* powerPoolText;
	irr::gui::IGUIStaticText* stationSelectedText;
	irr::gui::IGUIStaticText* helmStatus;
	irr::gui::IGUIStaticText* defenceStatus;
	irr::gui::IGUIStaticText* weaponStatus;
	irr::gui::IGUIStaticText* navigationStatus;
	irr::gui::IGUIScrollBar* scrollBar;
		
	irr::s32 counter;
	irr::gui::IGUIListBox* listbox;

	void SubscribeStation( Station *s );
	void UpdatePowerUsage(StationType s, int newValue );
	int GetPower(StationType stationType );
};

#endif