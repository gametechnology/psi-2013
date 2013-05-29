#include "PowerStation.h"

using namespace irr;
using namespace irr::gui;
using namespace irr::video;
using namespace irr::core;

PowerStation::PowerStation(Core* core, Interface* ui, Ship *ship) : Station(core, ui, ship)
{
	_interface = ui;

	context.counter = 0;
	context.powerPool = 100;
}

void PowerStation :: init() {
	_stationType = ST_POWER;
	setStationDestroyed(false);

	skin = _core->getGuiEnv()->getSkin();
	font = _core->getGuiEnv()->getFont( "../assets/Textures/Stations/PowerStation/fontcopperplategothicbold.png" );

	if (font)
		skin->setFont(font);
	else
		skin->setFont(_core->getGuiEnv()->getBuiltInFont(), EGDF_TOOLTIP);

	SubscribeStation(_ship->GetStation(ST_DEFENCE) );
	SubscribeStation(_ship->GetStation(ST_HELM) );
	SubscribeStation(_ship->GetStation(ST_NAVIGATION) );
	SubscribeStation(_ship->GetStation(ST_WEAPON) );
	SubscribeStation(this);

	Station::init();
}

PowerStation :: ~PowerStation()
{
	Station::~Station();
}

void PowerStation::handleNetworkMessage(NetworkPacket packet)
{

}

void PowerStation :: SubscribeStation( Station *s )
{
	context.SubscribeStation( s );
}

int PowerStation :: GetPower(StationType type)
{
	return context.GetPower(type);
}

void PowerStation :: UpdateStationPower(StationType s, int newValue )
{
	if ( s == ST_POWER )
		return;
	context.UpdatePowerUsage( s, newValue );
}

void PowerStation :: DoCameraShake( )
{
}

//Creates the User Interface. Is a helper method. Also initializes the event receiver.
void PowerStation::createUI()
{
	addImages();
	createPowerPool();
	createScrollbar();
	createButtons();
	createGeneralPowerTexts();
	createCurrentSelectedStationText();

	receiver = new MyEventReceiver(context, _core->getDevice());
	_core->getInput()->unsetCustomEventReceiver();
	_core->getInput()->setCustomEventReceiver(receiver);
}

void PowerStation::enable()
{
	(_ship)->help->setHelpText(L"Select a station by clicking on it's button\nGive power to the selected station by adjusting the slider.\ntodo: Exit station: 'Esc'");

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
}

//Creates the power scrollbar. 
void PowerStation::createScrollbar(){
	_interface->addScrollBar(false, 1200, 20, 30, 240, 0, GUI_ID_SCROLL_BAR);
	context.scrollBar = dynamic_cast<IGUIScrollBar*>(_interface->getElementWithId(GUI_ID_SCROLL_BAR));
	context.scrollBar->setMax(100);
	context.scrollBar->setSmallStep(1);
	context.scrollBar->setLargeStep(10);
	context.scrollBar->setPos(100);
}

//Creates the station buttons.
void PowerStation::createButtons(){
	_interface->createButton(870, 460, 60, 60, GUI_ID_POWER_HELM, 0, L"Helm Station");
	_interface->createButton(700, 560, 60, 60, GUI_ID_POWER_WEAPON, 0, L"Weapons Station");
	_interface->createButton(700, 310, 60, 60, GUI_ID_POWER_DEFENCE, 0, L"Defence Station");
	_interface->createButton(490, 310, 60, 60, GUI_ID_POWER_NAVIGATION, 0, L"Navigation Station");
}

//Creates the power status texts for the different stations.
void PowerStation::createGeneralPowerTexts()
{
	_interface->addStaticText(L"Helm power status: ", 300, 40, 500, 20, HELM_POWER_STATUS, false, true, false);
	_interface->addStaticText(L"Defense power status: ", 300, 70, 500, 20, DEFENSE_POWER_STATUS, false, true, false);
	_interface->addStaticText(L"Weapon power status: ", 300, 100, 500, 20, WEAPON_POWER_STATUS, false, true, false);
	_interface->addStaticText(L"Navigation power status: ", 300, 130, 500, 20, NAVIGATION_POWER_STATUS, false, true, false);

	context.helmStatus = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(HELM_POWER_STATUS));
	context.defenceStatus = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(DEFENSE_POWER_STATUS));
	context.weaponStatus = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(WEAPON_POWER_STATUS));
	context.navigationStatus = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(NAVIGATION_POWER_STATUS));

	context.helmStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
	context.defenceStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
	context.weaponStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
	context.navigationStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
}

//Creates the "Station selected: " text.
void PowerStation::createCurrentSelectedStationText()
{
	_interface->addStaticText(L"Station selected: ", 800, 40, 400, 80, SELECTED_STATION, false, true, false);

	context.stationSelectedText = dynamic_cast<IGUIStaticText*>(_interface->getElementWithId(SELECTED_STATION));
	context.stationSelectedText->setOverrideColor(video::SColor(255, 100, 125, 255));
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

	context.helmStatus->setText((varToString(		"Helm power status: ", (float)helm, "%")).c_str());
	context.defenceStatus->setText((varToString(	"Defence power status: ", (float)defence, "%")).c_str());
	context.weaponStatus->setText((varToString(		"Weapon power status: ", (float)weapon, "%")).c_str());
	context.navigationStatus->setText((varToString(	"Navigation power status: ", (float)navigation, "%")).c_str());

	//Checks the power percentage and assigns the text a color indicating the amount of power available to that station.
	changeColorAccordingToPowerStatus(*context.helmStatus, (float)helm);
	changeColorAccordingToPowerStatus(*context.defenceStatus, (float)defence);
	changeColorAccordingToPowerStatus(*context.weaponStatus, (float)weapon);
	changeColorAccordingToPowerStatus(*context.navigationStatus, (float)navigation);

	selectedStation();
}

void PowerStation::draw()
{
	_core->getDriver()->draw2DImage(_core->getDriver()->getTexture("../assets/Textures/Stations/PowerStation/black_bg.png"), 
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
		true);

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