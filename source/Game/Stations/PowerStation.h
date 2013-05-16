#ifndef POWER_STATION
#define POWER_STATION

#include "Station.h"
#include "..\Ship.h"
#include "PowerStationData.h"
#include <Engine\Game.h>
#include "../NetworkInterface.h"
#include "../HudHelpText.h"
#include <Irrlicht\irrlicht.h>
#include <time.h>
#include <iostream>

#define BOOST_TIME	10

class PowerStation : public Station, public INetworkListener
{
private:
	
	//checks if the new value can be matched (cannot be lower than 0 or higher than the total energy in our pool) and then updates the value of the station's energy pool.
	void UpdateStationPower(StationType, int newValue );

	irr::gui::IGUIImage* bgImage;
	irr::gui::IGUIImage* spaceshipImage;

	irr::gui::IGUIButton* helmButton;
	irr::gui::IGUIButton* weaponButton;
	irr::gui::IGUIButton* defenseButton;
	irr::gui::IGUIButton* navigationButton;

public:
	HudHelpText* help;

	//Power Station Impl	
	video :: IVideoDriver	*driver;
	IrrlichtDevice			*device;
	IGUIEnvironment			*env;
	IGUISkin				*skin;
	IGUIFont				*font;
	PowerStationData		context;

	PowerStation( Ship* ship );
	~PowerStation( void );
	bool IsPoolEmpty( );

	void SubscribeStation( Station *s );

	//shakes the camera whenever the station is hurt (aaaahh)
	void DoCameraShake( );
	
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
	stringw varToString(stringw str1, float var, stringw str2 = L"");
	
	virtual void init();
	virtual void update();
	virtual void draw();

	void selectedStation();
	void changeColorAccordingToPowerStatus(IGUIStaticText &staticText, float powerAmount);

	int GetPower(StationType type);
	void OnEnabled();
	void OnDisabled();
};

#endif