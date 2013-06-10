#include "PowerStation.h"
#include "GUIEventReceiver\PowerStationEventReveiver.h"

using namespace irr;
using namespace irr::gui;
using namespace irr::video;
using namespace irr::core;

typedef PowerStationEventReveiver PSER;

PowerStation::PowerStation(Ship *ship) : Station(ship)
{
	context.counter = 0;
	context.powerPool = 100;
	shipYpos = 100;
	scrollYpos = 266;
}

void PowerStation :: init() {
	_stationType = ST_POWER;
	setStationDestroyed(false);
	this -> guiEnv= this->game->guiEnv;	
	this -> setStationDestroyed(false);

	skin = game->guiEnv->getSkin();
	font = game->guiEnv->getFont( "../assets/Textures/Stations/PowerStation/fontcopperplategothicbold.png" );

	if (font)
		skin->setFont(font);
	else
		skin->setFont(game->guiEnv->getBuiltInFont(), EGDF_TOOLTIP);

	//SubscribeStation(_ship->GetStation(ST_DEFENCE) );
	SubscribeStation(_ship->GetStation(ST_HELM) );
	//SubscribeStation(_ship->GetStation(ST_NAVIGATION) );
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
	handleNetworkMessage(packet);
}

void PowerStation::handleNetworkMessage(NetworkPacket packet)
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

void PowerStation::OnEnabled()
{
}

void PowerStation::OnDisabled()
{
}

void PowerStation::removeUI()
{
	//Remove the static texts and scrollbars
	for (int i = 0; i < context.scrollBars.size(); i++)
	{
		context.scrollBars.at(i)->remove();
		context.stationsText.at(i)->remove();
	}

	//Clear lists
	context.scrollBars.clear();
	context.stationsText.clear();

	//Remove power text
	if(context.powerPoolText != NULL)
		context.powerPoolText->remove();
}

void PowerStation :: DoCameraShake( )
{
}

//Creates the User Interface. Is a helper method. Also initializes the event receiver.
void PowerStation::createUI()
{
	//declareUIData();
	addImages();
	createPowerPoolText();

	//create the panels (scrollbar and text) for every station
	createPowerStatusPanel(PSER::GUI_ID_SCROLL_BAR_HELM, 840, 150, 200, 30, 30,			PSER::GUI_ID_TEXT_HELM);
	//createPowerStatusPanel(PSER::GUI_ID_SCROLL_BAR_DEFENCE, 320, 150, 200, 30, 60,		PSER::GUI_ID_TEXT_DEFENCE);
	createPowerStatusPanel(PSER::GUI_ID_SCROLL_BAR_WEAPON, 580, 150, 200, 30, 30,		PSER::GUI_ID_TEXT_WEAPON);
	//createPowerStatusPanel(PSER::GUI_ID_SCROLL_BAR_NAVIGATION, 840, 150, 200, 30, 60,	PSER::GUI_ID_TEXT_NAVIGATION);

	receiver = new PSER(context, game->device);

	game->input->unsetCustomEventReceiver();
	game->input->setCustomEventReceiver(receiver);
}

void PowerStation::enable()
{
	(_ship)->help->setHelpText(L"Drag sliders to adjust power for its station.");

	createUI();
	context.scrollBars.at(0)->setPos(this->_ship->GetStation(StationType::ST_HELM)->getPower());
	context.scrollBars.at(1)->setPos(this->_ship->GetStation(StationType::ST_WEAPON)->getPower());
	//context.UpdatePowerUsage(StationType::ST_WEAPON, this->_ship->GetStation(StationType::ST_WEAPON)->getPower(), false);
	Station::enable();
}

void PowerStation::disable()
{
	removeUI();
	enabled = false;
	Station::disable();
}

//Creates the text for the power pool along with its value.
void PowerStation::createPowerPoolText()
{
	stringw str = varToString("Power Pool:\n", POWER_MAX, "%");
	context.powerPoolText = guiEnv->addStaticText(str.c_str(), rect<s32>(40, 40, 240, 200), false, true, NULL, PowerStationEventReveiver::POWER_POOL_STATUS, false);
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
	spaceshipImage = game->driver->getTexture("../assets/Textures/Stations/PowerStation/powerstation.png");

}

void PowerStation::createPowerStatusPanel(int scrollBarID, int x, int y, int width, int height, int textOffset, int staticTextID)
{
	//create a scrollbar
	createScrollbar(scrollBarID, x, y, width, height);

	//Create a static text above the scrollbar
	createText(staticTextID, x, y - textOffset, width, height);
}

//Creates a power scrollbar. 
void PowerStation::createScrollbar(int scrollBarID, int x, int y, int width, int height){
	context.scrollBars.push_back(guiEnv->addScrollBar(true, rect<s32>(x, y, width + x, height + y), NULL, scrollBarID));
	context.scrollBars.back()->setMax(100);
	context.scrollBars.back()->setSmallStep(1);
	context.scrollBars.back()->setLargeStep(100);
	context.scrollBars.back()->setPos(0);
	context.scrollBars.back()->setVisible(true);	
}

//Creates a power status texts for the different stations.
void PowerStation::createText(int staticTextID, int x, int y , int width, int height)
{
	context.stationsText.push_back(guiEnv->addStaticText(L"", rect<s32>(x, y, width + x, height + y), false, true, NULL, staticTextID, false));
	context.stationsText.back()->setOverrideColor(video::SColor(255, 0, 255, 0));
}

//This method needs to be called every frame. It displays and updates the power status numbers of the different stations.
void PowerStation::update()
{
	Station::update();

	//If enabled we update sliders
	if(enabled)
	{
		int helm = context.GetPower(ST_HELM);
		//int defence	= context.GetPower(ST_DEFENCE);
		int weapon = context.GetPower(ST_WEAPON);
		//int navigation = context.GetPower(ST_NAVIGATION);

		context.powerPoolText->setText((varToString("Power Pool:\n", (float)context.powerPool, "%")).c_str());

		//Set text to stationtexts
		context.stationsText.at(0)->setText((varToString("Helm : ", (float)helm, "%")).c_str());
		//context.stationsText.at(1)->setText((varToString("Defence: ", (float)defence, "%")).c_str());
		context.stationsText.at(1)->setText((varToString("Weapon: ", (float)weapon, "%")).c_str());
		//context.stationsText.at(3)->setText((varToString("Navigation: ", (float)navigation, "%")).c_str());

		//Checks the power percentage and assigns the text a color indicating the amount of power available to that station.
		changeColorAccordingToPowerStatus(*context.stationsText.at(0), (float)helm);
		//changeColorAccordingToPowerStatus(*context.stationsText.at(1), (float)defence);
		changeColorAccordingToPowerStatus(*context.stationsText.at(1), (float)weapon);
		//changeColorAccordingToPowerStatus(*context.stationsText.at(3), (float)navigation);

		//Update sliders
		updateSliders();
	}
}

void PowerStation::updateSliders()
{
	//Update the slider pos
	for(int i = 0; i < context.scrollBars.size(); i++)
	{
		context.scrollBars.at(i)->setMax(context.scrollBars.at(i)->getPos() + context.powerPool);
	}

	//context.UpdatePowerUsage(StationType::ST_DEFENCE, context.scrollBars.at(0)->getPos(), false);
	context.UpdatePowerUsage(StationType::ST_HELM, context.scrollBars.at(0)->getPos(), false);
	context.UpdatePowerUsage(StationType::ST_WEAPON, context.scrollBars.at(1)->getPos(), false);


}

void PowerStation::draw()
{
	
	if(enabled)
	{
		game->driver->draw2DImage(game->driver->getTexture("../assets/Textures/Stations/PowerStation/black_bg.png"), 
			position2d<s32>(0,0),
			rect<s32>(0, 0, 1280, 720), 
			0,
			SColor(255, 255, 255, 255),
			true);
		game->driver->draw2DImage(spaceshipImage, core::position2d<s32>(110,190),
		irr::core::rect<s32>(0,0,spaceshipImage->getOriginalSize().Width, spaceshipImage->getOriginalSize().Height),
		0, video::SColor(255,255,255,255), true);
	}
	
	Station::draw();
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