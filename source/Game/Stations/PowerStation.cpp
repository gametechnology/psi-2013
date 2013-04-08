#include "PowerStation.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <math.h>

PowerStation :: PowerStation( Ship *ship ) : Station( ship )
{
	this -> _stationType		= StationType :: Power;
	this -> device				= Game :: device;
	this ->	driver				= device -> getVideoDriver( );
	this -> env					= device -> getGUIEnvironment( );	
}

PowerStation :: ~PowerStation()
{

}

void PowerStation :: SubscribeStation( Station *s )
{
	this -> context.SubscribeStation( s );
}

int PowerStation :: GetPower(Station::StationType type)
{
	return this->context.GetPower(type);
}

void PowerStation :: UpdateStationPower( Station :: StationType s, int newValue )
{
	if ( s == STATION_TYPE :: Power )	return;	//we do nothing when the power station is selected.
	this -> context.UpdatePowerUsage( s, newValue );
}

void PowerStation :: DoCameraShake( )
{
	//here, we are going to do the Harlem Shake
}

// Define some values that we'll use to identify individual GUI controls.
enum
{
	GUI_ID_LEAVE_BUTTON = 101,
	GUI_ID_POWER_DEFENCE,
	GUI_ID_POWER_HELM,
	GUI_ID_POWER_WEAPON,
	GUI_ID_POWER_NAVIGATION,
	GUI_ID_SCROLL_BAR
};

/*
The Event Receiver is not only capable of getting keyboard and
mouse input events, but also events of the graphical user interface
(gui). There are events for almost everything: Button click,
Listbox selection change, events that say that a element was hovered
and so on. To be able to react to some of these events, we create
an event receiver.
We only react to gui events, and if it's such an event, we get the
id of the caller (the gui element which caused the event) and get
the pointer to the gui environment.
*/
class MyEventReceiver : public IEventReceiver
{

public:

	MyEventReceiver(UIData & context) : _context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Game::device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			/*
			If a scrollbar changed its scroll position, and it is
			'our' scrollbar (the one with id GUI_ID_SCROLL_BAR), then we update the power usage of that station.
			*/
			case EGET_SCROLL_BAR_CHANGED:
				s32 pos;
				
				if(_context.selectedStation == 1)
				{
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();					
					_context.UpdatePowerUsage( Station :: StationType :: Helm, POWER_MAX - pos );
				}
				else if(_context.selectedStation == 2){
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					_context.UpdatePowerUsage( Station :: StationType :: Defence, POWER_MAX - pos );
				}
				else if(_context.selectedStation == 3){
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					_context.UpdatePowerUsage( Station :: StationType :: Navigation, POWER_MAX - pos );
				}
				else if(_context.selectedStation == 4){
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();

					((IGUIScrollBar*)event.GUIEvent.Caller)->setPos( irr :: s32( ) );
					_context.UpdatePowerUsage( Station :: StationType :: Weapon, POWER_MAX - pos );
				}
				break;

			//If the user selected a button, check to see which button was clicked.
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case GUI_ID_LEAVE_BUTTON:
					Game::device->closeDevice();
					return true;
				case GUI_ID_POWER_HELM:
					_context.scrollBar->setVisible(true);
					_context.scrollBar->setPos(POWER_MAX - _context.GetPower( Station :: StationType :: Helm ) );
					_context.selectedStation = 1;

					break;
				case GUI_ID_POWER_DEFENCE:
					_context.scrollBar->setVisible(true);
					_context.scrollBar->setPos(POWER_MAX - _context.GetPower( Station :: StationType :: Defence ));
					_context.selectedStation = 2;
					break;
				case GUI_ID_POWER_NAVIGATION:
					_context.scrollBar->setVisible(true);
					_context.scrollBar->setPos(POWER_MAX - _context.GetPower( Station :: StationType :: Navigation));
					_context.selectedStation = 3;
					break;
				case GUI_ID_POWER_WEAPON:
					_context.scrollBar->setVisible(true);
					_context.scrollBar->setPos(POWER_MAX - _context.GetPower( Station :: StationType :: Weapon ));
					_context.selectedStation = 4;
					break;
					//TODO: change name
				case GUI_ID_SCROLL_BAR:
					break;
				default:
					_context.selectedStation = 0;
					_context.scrollBar->setVisible(false);
					break;
				}
				break;
			}
		}

		return false;
	}

private:
	UIData & _context;
};

//Initializes the User Interface.
void PowerStation::Initialize()
{
	Station :: Initialize( );
	
	skin = env->getSkin( );
	font = env->getFont( "../assets/Textures/Stations/PowerStation/fontcopperplategothicbold.png" );
	
	if (font)
		skin->setFont(font);
	else
		skin->setFont(env->getBuiltInFont(), EGDF_TOOLTIP);
	createUI();
	gameLoop( );
}
//Creates the User Interface. Is a helper method. Also initializes the event receiver.
void PowerStation::createUI()
{
	declareUIData();
	addImages();
	createPowerPool();
	createScrollbar();
	createButtons();
	createGeneralPowerTexts();
	createCurrentSelectedStationText();

	// Create the event receiver, giving it that context structure.
	MyEventReceiver *receiver = new MyEventReceiver(context);
	// And tell the device to use our custom event receiver.
	device -> setEventReceiver( receiver );
}

//Defines the used driver and some UI data values.
void PowerStation::declareUIData()
{
	context.counter = 0;
	context.powerPool = 100;
}
//Creates the text for the power pool along with its value.
void PowerStation::createPowerPool(){
	stringw str = varToString("Power Pool:\n", POWER_MAX, "%");

	context.powerPoolText = env->addStaticText(str.c_str(), rect<s32>(40, 40, 200, 100), false);
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
	env->addImage(driver->getTexture("../assets/Textures/Stations/PowerStation/black_bg.png"), position2d<int>(0,0));
	env->addImage(driver->getTexture("../assets\\Textures\\Stations\\PowerStation\\spaceship.png"), position2d<int>(190,266));
}
//Creates the power scrollbar. 
void PowerStation::createScrollbar(){
	context.scrollBar = env->addScrollBar(false, rect<s32>(1200, 20, 1230, 260), 0, GUI_ID_SCROLL_BAR);
	context.scrollBar->setMax(100);
	context.scrollBar->setSmallStep(1);
	context.scrollBar->setLargeStep(10);
	context.scrollBar->setPos(100);
}

//Creates the station buttons.
void PowerStation::createButtons(){
	IGUIButton *helmbut;
	helmbut = env->addButton(rect<s32>(870, 460, 930, 520),0, GUI_ID_POWER_HELM,L"HLM",L"Helm Station");

	IGUIButton *weaponbut;
	weaponbut = env->addButton(rect<s32>(700, 560, 790, 660),0, GUI_ID_POWER_WEAPON,L"WPN",L"Weapons Station");

	IGUIButton *defencebut;
	defencebut = env->addButton(rect<s32>(700, 310, 790, 410),0, GUI_ID_POWER_DEFENCE,L"DEF",L"Defence Station");

	IGUIButton *navigationbut;
	navigationbut = env->addButton(rect<s32>(490, 310, 580, 410),0, GUI_ID_POWER_NAVIGATION,L"NAV",L"Navigation Station");

	//Placeholder code for Communication Station.

	//IGUIButton *commbut;
	//commbut = env->addButton(rect<s32>(700, 310, 790, 410),0, GUI_ID_POWER_COMM,L"",L"Communication Station");

}

//Creates the power status texts for the different stations.
void PowerStation::createGeneralPowerTexts(){
	
	context.helmStatus = env->addStaticText(L"Helm power status: ", rect<s32>(300, 40, 800, 60), false);
	context.defenceStatus = env->addStaticText(L"defence power status: ", rect<s32>(300, 70, 800, 90), false);
	context.weaponStatus = env->addStaticText(L"Weapon power status: ", rect<s32>(300, 100, 800, 120), false);
	context.navigationStatus = env->addStaticText(L"Navigation power status: ", rect<s32>(300, 130, 800, 150), false);

	context.helmStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
	context.defenceStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
	context.weaponStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
	context.navigationStatus->setOverrideColor(video::SColor(255, 0, 255, 0));
}

//Creates the "Station selected: " text.
void PowerStation::createCurrentSelectedStationText(){
	context.stationSelectedText = env->addStaticText(L"Station selected: ", rect<s32>(800, 40, 1200, 120), false);
	context.stationSelectedText->setOverrideColor(video::SColor(255, 100, 125, 255));
}


//This method needs to be called every frame. It displays and updates the power status numbers of the different stations.
//TODO: FIND OUT HOW TO UPDATE ALL
void PowerStation::update()
{
	int helm		= context.GetPower( STATION_TYPE :: Helm );
	int defence		= context.GetPower( STATION_TYPE :: Defence );
	int weapon		= context.GetPower( STATION_TYPE :: Weapon );
	int navigation	= context.GetPower( STATION_TYPE :: Navigation );

	context.powerPoolText->setText((varToString("Power Pool:\n", context.powerPool, "%")).c_str());

	context.helmStatus->setText((varToString(		"Helm power status: ", helm, "%")).c_str());
	context.defenceStatus->setText((varToString(	"Defence power status: ", defence, "%")).c_str());
	context.weaponStatus->setText((varToString(		"Weapon power status: ", weapon, "%")).c_str());
	context.navigationStatus->setText((varToString(	"Navigation power status: ", navigation, "%")).c_str());

	//Checks the power percentage and assigns the text a color indicating the amount of power available to that station.
	changeColorAccordingToPowerStatus(*context.helmStatus, helm);
	changeColorAccordingToPowerStatus(*context.defenceStatus, defence);
	changeColorAccordingToPowerStatus(*context.weaponStatus, weapon);
	changeColorAccordingToPowerStatus(*context.navigationStatus, navigation);

	selectedStation();
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

void PowerStation :: gameLoop( )
{
	 while(Game::device->run() && driver)
	 if (Game::device->isWindowActive())
	 {
		  driver->beginScene(true, true, SColor(0,200,200,200));
		  update( );
		  env->drawAll();
		  driver->endScene();	  
	 }
	 Game::device->drop();
}