#include "PowerStation.h"

using namespace irr;
using namespace irr::gui;
using namespace irr::video;
using namespace irr::core;

PowerStation::PowerStation(Ship *ship) : Station(core, ui, ship)
{
	context.counter = 0;
	context.powerPool = 100;
}

void PowerStation :: init() {
	_stationType = ST_POWER;
	setStationDestroyed(false);
	this -> device				= this->game->device;
	//this ->	driver				= device -> getVideoDriver( );
	this -> env					= this->game->guiEnv;	
	this -> setStationDestroyed(false);

	skin = game->guiEnv->getSkin();
	font = game->guiEnv->getFont( "../assets/Textures/Stations/PowerStation/fontcopperplategothicbold.png" );

	if (font)
		skin->setFont(font);
	else
		skin->setFont(game->guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

	SubscribeStation(_ship->GetStation(ST_DEFENCE) );
	SubscribeStation(_ship->GetStation(ST_HELM) );
	SubscribeStation(_ship->GetStation(ST_NAVIGATION) );
	SubscribeStation(_ship->GetStation(ST_WEAPON) );
	SubscribeStation(this);

	Station::init();
	Network::GetInstance()->AddListener(CLIENT_POWER_CHANGED, this);
	Network::GetInstance()->AddListener(SERVER_POWER_CHANGED, this);

}

PowerStation :: ~PowerStation()
{
	Station::~Station();
}

void PowerStation::HandleNetworkMessage(NetworkPacket packet)
{
	unsigned int stationName;
	unsigned int stationValue;
	packet >> stationName;
	packet >> stationValue;

	StationType type = (StationType)stationName;
	unsigned int newValue = stationValue;

	UpdateStationPower(type, newValue, true);

	if(packet.GetType() == CLIENT_POWER_CHANGED)
	{
		NetworkPacket serverPacket(SERVER_POWER_CHANGED);
		serverPacket << type;
		serverPacket << newValue;
		Network::GetInstance()->SendPacketToAllClients(serverPacket, true);
	}
}

void PowerStation :: SubscribeStation(Station *station)
{
	context.SubscribeStation(station);
}

int PowerStation :: GetPower(StationType type)
{
	return context.GetPower(type);
}

void PowerStation :: UpdateStationPower(StationType type, int newValue, bool sentByServer )
{
	if ( type == ST_POWER )	return;	//we do nothing when the power station is selected.
	this -> context.UpdatePowerUsage( type, newValue, sentByServer );
}

void PowerStation :: DoCameraShake( )
{
}

//Creates the User Interface. Is a helper method. Also initializes the event receiver.
void PowerStation::createUI()
{
	declareUIData();
	addImages();
	createPowerPool();
	
	//create the panels (scrollbar and text) for every station
	createPowerStatusPanel(GUI_ID_SCROLL_BAR_DEFENCE, 60, 600, 200, 30, 60, GUI_ID_TEXT_DEFENCE);
	createPowerStatusPanel(GUI_ID_SCROLL_BAR_HELM, 320, 600, 200, 30, 60, GUI_ID_TEXT_HELM);
	createPowerStatusPanel(GUI_ID_SCROLL_BAR_WEAPON, 580, 600, 200, 30, 60, GUI_ID_TEXT_WEAPON);
	createPowerStatusPanel(GUI_ID_SCROLL_BAR_NAVIGATION, 840, 600, 200, 30, 60, GUI_ID_TEXT_NAVIGATION);

	//TODO: Create images instead of buttons
	//createButtons();
	
	receiver = new PowerStationEventReceiver(context, game->device);

	game->input->unsetCustomEventReceiver();
	game->input->setCustomEventReceiver(receiver);
}

void PowerStation::enable()
{
	(_ship)->help->setHelpText(L"Drag sliders to adjust power for its station.");

	createUI();
	Station::enable();
}

void PowerStation::disable()
{
	_interface->resetInterface();
	Station::disable();
}

//Creates the text for the power pool along with its value.
void PowerStation::createPowerPool()
{
	stringw str = varToString("Power Pool:\n", POWER_MAX, "%");

	_interface->addStaticText(str.c_str(), 40, 40, 200, 100, POWER_POOL_STATUS, false, true, false);
	context.powerPoolText = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(POWER_POOL_STATUS));
	context.powerPoolText->setOverrideColor(video::SColor(255, 0, 255, 0));
}

//Variable to string converter for printing to the screen.
stringw PowerStation::varToString(stringw str1, float var, stringw str2){
	stringw str = L"";
	str += str1;
	str += (int)var;
	str += str2;
	return str;
}

//Adds the background image and the spaceship image. 
void PowerStation::addImages()
{
	_interface->addImage("../assets/Textures/Stations/PowerStation/black_bg.png", 0,0);
	_interface->addImage("../assets/Textures/Stations/PowerStation/spaceship.png", 190, 266);


	_interface->addImage("../assets/shipmap/icon_helm.png", 890, 460);
	_interface->addImage("../assets/shipmap/icon_defense.png", 520, 610);
	_interface->addImage("../assets/shipmap/icon_weapons.png", 590, 330);
	_interface->addImage("../assets/shipmap/icon_navigation.png", 705, 595);
	_interface->addImage("../assets/shipmap/icon_engine.png", 260, 460);

}

void PowerStation::createPowerStatusPanel(int scrollBarID, int x, int y, int width, int height, int textOffset, int staticTextID)
{
	//create a scrollbar
	createScrollbar(scrollBarID, x, y, width, height);

	//Create a static text above the scrollbar
	createText(staticTextID, x, y - textOffset, width, height);

	//Create images for stations
}

//Creates the power scrollbar. 
void PowerStation::createScrollbar(int scrollBarID, int x, int y, int width, int height){
	_interface->addScrollBar(true, x, y, width, height, 0, scrollBarID);
	context.scrollBars.push_back(dynamic_cast<IGUIScrollBar*>(_interface->getElementWithId(scrollBarID)));
	context.scrollBars.back()->setMax(100);
	context.scrollBars.back()->setSmallStep(1);
	context.scrollBars.back()->setLargeStep(100);
	context.scrollBars.back()->setPos(100);
	context.scrollBars.back()->setVisible(true);	
}
/*
//Creates the station buttons.
void PowerStation::createButtons(){
	_interface->createButton(870, 460, 60, 60, GUI_ID_POWER_HELM, 0, L"Helm Station");
	_interface->createButton(700, 560, 60, 60, GUI_ID_POWER_WEAPON, 0, L"Weapons Station");
	_interface->createButton(700, 310, 60, 60, GUI_ID_POWER_DEFENCE, 0, L"Defence Station");
	_interface->createButton(490, 310, 60, 60, GUI_ID_POWER_NAVIGATION, 0, L"Navigation Station");
}
*/
//Creates the power status texts for the different stations.
void PowerStation::createText(int staticTextID, int x, int y , int width, int height)
{
	_interface->addStaticText(L"TEST", x, y, width, height, staticTextID, false, true, false);
	context.stationsText.push_back(dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(staticTextID)));
	context.stationsText.back()->setOverrideColor(video::SColor(255, 0, 255, 0));
}



//This method needs to be called every frame. It displays and updates the power status numbers of the different stations.
//TODO: FIND OUT HOW TO UPDATE ALL
void PowerStation::update()
{
	Station::update();
	
	int helm = context.GetPower(ST_HELM);
	int defence	= context.GetPower(ST_DEFENCE);
	int weapon = context.GetPower(ST_WEAPON);
	int navigation = context.GetPower(ST_NAVIGATION);

	context.powerPoolText->setText((varToString("Power Pool:\n", (float)context.powerPool, "%")).c_str());
	/*
	//Set text to stationtexts
	context.stationsText.at(0)->setText((varToString("Helm power: ", (float)helm, "%")).c_str());
	context.stationsText.at(1)->setText((varToString("Defence power: ", (float)defence, "%")).c_str());
	context.stationsText.at(2)->setText((varToString("Weapon power: ", (float)weapon, "%")).c_str());
	context.stationsText.at(3)->setText((varToString("Navigation power: ", (float)navigation, "%")).c_str());
	
	Checks the power percentage and assigns the text a color indicating the amount of power available to that station.
	changeColorAccordingToPowerStatus(*context.stationsText.at(0), (float)helm);
	changeColorAccordingToPowerStatus(*context.stationsText.at(1), (float)defence);
	changeColorAccordingToPowerStatus(*context.stationsText.at(2), (float)weapon);
	changeColorAccordingToPowerStatus(*context.stationsText.at(3), (float)navigation);
	*/
}

void PowerStation::draw()
{
	/*_core->getDriver()->draw2DImage(_core->getDriver()->getTexture("../assets/Textures/Stations/PowerStation/black_bg.png"), 
		position2d<s32>(0,0), 
		rect<s32>(0, 0, 1280, 720), 
		0,
		SColor(255, 255, 255, 255),
		true);
	_core->getDriver()->draw2DImage(_core->getDriver()->getTexture("../assets/Textures/Stations/PowerStation/spaceship.png"), 
		position2d<s32>(190, 266), 
		rect<s32>(0, 0, 1280, 720), 
		0,
		SColor(255, 255, 255, 255),
		true);*/

	Station::draw();
}

//This method displays the selected station. We're using an integer which indicates which station is currently selected. 
//context.selectedStation gets changed by the EventListener when the user presses of the station buttons.
void PowerStation::selectedStation(){
	stringw str = L"";
	switch ( context.selectedStation )
	{
	case 1:
		str += "Station selected: \nHelm";
		break;
	case 2:
		str += "Station selected: \nDefence";
		break;
	case 3:
		str += "Station selected: \nNavigation";
		break;
	case 4:
		str += "Station selected: \nWeapon";
		break;
	default:
		str += "Station selected: ";
		break;
	}
	context.stationSelectedText->setText(str.c_str());
	context.stationSelectedText->setOverrideColor(video::SColor(255, 100, 125, 255));
}


//This Method changes the color according to power status by looking at the amount of power a station has. 
//changeColorAccordingToPowerStatus needs to be called once every frame. This is done by the updateAll() method.
void PowerStation::changeColorAccordingToPowerStatus(IGUIStaticText &stcTxt, float powerAmount){
	//if power is equal or greater than 15, make the text color green.
	if(powerAmount >= 15.0f){
		stcTxt.setOverrideColor(video::SColor(255, 0, 255, 0));
	}
	//if power is lower than 15 but higher than 5, make the text color yellow.
	else if(powerAmount < 15.0f && powerAmount >= 5.0f){
		stcTxt.setOverrideColor(video::SColor(255, 255, 255, 0));
	}
	//if power is lower than 5 and equal or higher than 0, make the text color red.
	else if(powerAmount > 0.0f && powerAmount < 5.0f){
		stcTxt.setOverrideColor(video::SColor(255, 255, 0, 0));
	} 
	//if power is 0, make the text color gray.
	else if(powerAmount == 0.0f){
		stcTxt.setOverrideColor(video::SColor(255, 180, 180, 180));
	}
}