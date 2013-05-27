#ifndef POWER_STATION
#define POWER_STATION

#include <Irrlicht/irrlicht.h>
#include <Engine/Core.h>

#include <time.h>
#include <iostream>

#include "Station.h"
#include "../Ship.h"
#include "PowerStationData.h"
#include "../NetworkInterface.h"
#include "../HudHelpText.h"

/*
* TODO Refactor the station. There
* are too many functions.
*/

// Prefer constants over Defines.
const int BOOST_TIME = 10;

class PowerStation : public Station, public INetworkListener
{
public:
	//Power Station Impl	
	irr::video::IVideoDriver *driver;
	irr::IrrlichtDevice *device;
	irr::gui::IGUIEnvironment *env;
	irr::gui::IGUISkin *skin;
	irr::gui::IGUIFont *font;
	PowerStationData context;

	PowerStation(Ship* ship);
	~PowerStation();

	bool IsPoolEmpty();

	void SubscribeStation(Station *s);

	//shakes the camera whenever the station is hurt (aaaahh)
	void DoCameraShake( );
	
	void enable();
	void disable();
	void createUI();
	void removeUI();
	void addImages();
	void removeImages();

	void declareUIData();

	void createPowerPool();
	void createScrollbar();
	void createButtons();
	void createGeneralPowerTexts();
	void createCurrentSelectedStationText();

	void HandleNetworkMessage(NetworkPacket packet);
	irr::core::stringw varToString(irr::core::stringw str1, float var, irr::core::stringw str2 = L"");
	
	virtual void init();
	virtual void update();
	virtual void draw();


	void selectedStation();
	void changeColorAccordingToPowerStatus(irr::gui::IGUIStaticText& staticText, float powerAmount);

	int GetPower(StationType type);
	void OnEnabled();
	void OnDisabled();
private:	
	//checks if the new value can be matched (cannot be lower than 0 or higher than the total energy in our pool) and then updates the value of the station's energy pool.
	void UpdateStationPower(StationType, int newValue );
};

#endif