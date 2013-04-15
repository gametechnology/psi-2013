#ifndef POWER_STATION
#define POWER_STATION

#include "Station.h"
#include "..\Ship.h"
#include "UIData.h"
#include <time.h>
#include <iostream>

#define BOOST_TIME	10

class PowerStation : public Station 
{
private:
	
	//checks if the new value can be matched (cannot be lower than 0 or higher than the total energy in our pool) and then updates the value of the station's energy pool.
	void UpdateStationPower( Station :: StationType, int newValue );	

public:
	//Power Station Impl	
	//video :: IVideoDriver	*driver;
	IrrlichtDevice			*device;
	IGUIEnvironment			*env;
	IGUISkin				*skin;
	IGUIFont				*font;
	UIData					context;

	PowerStation( Ship* ship );
	~PowerStation( void );
	bool IsPoolEmpty( );

	void SubscribeStation( Station *s );

	//shakes the camera whenever the station is hurt (aaaahh)
	void DoCameraShake( );
	
	void Initialize();
	void createUI();
	void addImages();
	void declareUIData();
	void createPowerPool();
	void createScrollbar();
	void createButtons();
	void createGeneralPowerTexts();
	void createCurrentSelectedStationText();
	stringw varToString(stringw str1, float var, stringw str2 = L"");

	void update();
	void draw();

	void selectedStation();
	void changeColorAccordingToPowerStatus(IGUIStaticText &staticText, float powerAmount);

	int GetPower(Station::StationType type);
};

#endif