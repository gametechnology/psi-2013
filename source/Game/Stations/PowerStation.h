#ifndef POWER_STATION
#define POWER_STATION

#include <time.h>
#include <iostream>
#include <math.h>
#include "Station.h"
#include "PowerStationData.h"
#include "../NetworkInterface.h"
#include "../Ship.h"

using namespace irr::core;

//Predefine classes
class PowerStationEventReveiver;

// Prefer constants over Defines.
const int BOOST_TIME = 10;


class PowerStation : public Station, public INetworkListener
{
public:
	//Power Station Impl	
	irr::gui::IGUISkin *skin;
	irr::gui::IGUIFont *font;
	PowerStationData context;
	irr::gui::IGUIEnvironment* guiEnv;

	PowerStation(Ship*);
	~PowerStation();

	void SubscribeStation(Station *s);

	//shakes the camera whenever the station is hurt (aaaahh)
	void DoCameraShake( );
	
	virtual void enable();
	virtual void disable();
	void createUI();
	void addImages();

	//New interface
	void createPowerStatusPanel(int scrollBarID, int x, int y, int width, int height, int textOffset, int staticTextID);
	void createScrollbar(int scrollBarID, int x, int y, int width, int height);
	void createText(int staticTextID, int x, int y , int width, int height);
	void createPowerPoolText();
	//void createButtons();
	virtual void HandleNetworkMessage(NetworkPacket packet); //Inet version
	virtual void handleNetworkMessage(NetworkPacket packet); //Station version
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
	void UpdateStationPower(StationType, int newValue, bool sentByServer );

	PowerStationEventReveiver* receiver;
	float shipYpos;
	float scrollYpos;
	video::ITexture* icon_helm;
	video::ITexture* icon_defense;
	video::ITexture* icon_weapons;
	video::ITexture* icon_navigation;
	video::ITexture* icon_engine;
};

#endif