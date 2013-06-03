#ifndef POWER_STATION
#define POWER_STATION

#include <Engine/Interface.h>

#include <time.h>
#include <iostream>
#include <math.h>

#include "Station.h"

#include "PowerStationData.h"
#include "../NetworkInterface.h"


#include "../Ship.h"
#include "GUIEventReceiver/PowerStationEventReceiver.h"

using namespace irr::core;

/*
* TODO Refactor the station. There
* are too many functions.
*/

// Prefer constants over Defines.
const int BOOST_TIME = 10;

enum
{
	GUI_ID_LEAVE_BUTTON = 101,
	GUI_ID_POWER_DEFENCE,
	GUI_ID_POWER_HELM,
	GUI_ID_POWER_WEAPON,
	GUI_ID_POWER_NAVIGATION,

	//Scroll bars
	GUI_ID_SCROLL_BAR_DEFENCE,
	GUI_ID_SCROLL_BAR_HELM,
	GUI_ID_SCROLL_BAR_NAVIGATION,
	GUI_ID_SCROLL_BAR_WEAPON,

	//static texts
	GUI_ID_TEXT_DEFENCE,
	GUI_ID_TEXT_HELM,
	GUI_ID_TEXT_NAVIGATION,
	GUI_ID_TEXT_WEAPON,

	POWER_POOL_STATUS,
	SELECTED_STATION
};


class PowerStation : public Station, public INetworkListener
{
public:
	//Power Station Impl	
	irr::gui::IGUISkin *skin;
	irr::gui::IGUIFont *font;
	PowerStationData context;

	PowerStation(Core*, Interface*, Ship*);
	~PowerStation();

	bool IsPoolEmpty();

	void SubscribeStation(Station *s);

	//shakes the camera whenever the station is hurt (aaaahh)
	void DoCameraShake( );
	
	virtual void enable();
	virtual void disable();
	void createUI();
	void addImages();
	void removeImages();

	//New interface
	void createPowerStatusPanel(int scrollBarID, int x, int y, int width, int height, int textOffset, int staticTextID);
	void createScrollbar(int scrollBarID, int x, int y, int width, int height);
	void createText(int staticTextID, int x, int y , int width, int height);

	void createPowerPool();
	//void createButtons();
	

	virtual void handleNetworkMessage(NetworkPacket packet);
	irr::core::stringw varToString(irr::core::stringw str1, float var, irr::core::stringw str2 = L"");
	
	virtual void init();
	virtual void update();
	virtual void draw();

	void changeColorAccordingToPowerStatus(irr::gui::IGUIStaticText& staticText, float powerAmount);

	int GetPower(StationType type);
	void OnEnabled();
	void OnDisabled();
private:	
	//checks if the new value can be matched (cannot be lower than 0 or higher than the total energy in our pool) and then updates the value of the station's energy pool.
	void UpdateStationPower(StationType, int newValue );

	MyEventReceiver* receiver;
};

#endif