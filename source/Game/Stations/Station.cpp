#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"

Station :: Station( Ship *ship )
{
	this ->	_ship	= ship;

	//this -> _switchTime = 4.0f;
}

bool Station::HasPlayer()
{
	return ( this -> _player != NULL );
}

bool Station::SwitchTimePassed()
{
	return this -> _playerOnStationTime > this -> _switchTime;
}

STATION_TYPE Station :: GetStationType( )
{
	return this -> _stationType;
}

bool Station::IsStunned()
{
	time_t *t;
	time( t );

	//return true if the difference between the current time and the time the station was stunned is less than the defined stun time
	return difftime( *_stunTime, *t ) <= STUN_TIME;
}

void Station::Update(float time)
{
	//Update Stun Time
	//Update player on station time	
}

void Station :: OnDamage( )
{	
	//set the stun time to the current time (the time when it was stunned) 
	time( _stunTime );
}

bool Station::HasPower( )
{
	return true;//this->_ship->_powerStation->GetPower(this->_stationType) > 0;
}

bool Station::HasArmor( )
{
	return true;//this->_ship->_defenceStation->GetArmor(this->_stationType) > 0;
}

void Station :: Initialize( )
{
	this -> _player = NULL;
	this -> _playerOnStationTime = 0;
	this -> _stunTime = 0;
	this -> _switchTime = 0;

	if ( this -> _stationType != StationType ::  Power )	this -> _ship -> _powerStation		-> SubscribeStation( this );
	if ( this -> _stationType != StationType ::  Defence )	this -> _ship -> _defenceStation	-> SubscribeStation( this );
}
/*
class MyEventReceiver : public IEventReceiver
{

public:

	MyEventReceiver(UIData & context) : Context(context) { }

	virtual bool OnEvent(const SEvent& event)
	{
		if (event.EventType == EET_GUI_EVENT)
		{
			s32 id = event.GUIEvent.Caller->getID();
			IGUIEnvironment* env = Context.device->getGUIEnvironment();

			switch(event.GUIEvent.EventType)
			{

			/*
			If a scrollbar changed its scroll position, and it is
			'our' scrollbar (the one with id GUI_ID_SCROLL_BAR), then we update the power usage of that station.
			*//*
			case EGET_SCROLL_BAR_CHANGED:
				s32 pos;
				
				if(Context.selectedStation == 1)
				{
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();					
					Context.UpdatePowerUsage( Station :: StationType :: Helm, POWER_MAX - pos );
				}
				else if(Context.selectedStation == 2){
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					Context.UpdatePowerUsage( Station :: StationType :: Defence, POWER_MAX - pos );
				}
				else if(Context.selectedStation == 3){
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();
					Context.UpdatePowerUsage( Station :: StationType :: Navigation, POWER_MAX - pos );
				}
				else if(Context.selectedStation == 4){
					pos = ((IGUIScrollBar*)event.GUIEvent.Caller)->getPos();

					((IGUIScrollBar*)event.GUIEvent.Caller)->setPos( irr :: s32( ) );
					Context.UpdatePowerUsage( Station :: StationType :: Weapon, POWER_MAX - pos );
				}
				break;

			//If the user selected a button, check to see which button was clicked.
			case EGET_BUTTON_CLICKED:
				switch(id)
				{
				case KEY_KEY_0 :
					Context.device->closeDevice();
					return true;
				case KEY_KEY_1 :
					Context.scrollBar->setVisible(true);
					Context.scrollBar->setPos(POWER_MAX - Context.GetPower( Station :: StationType :: Helm ) );
					Context.selectedStation = 1;

					break;
				case KEY_KEY_2 :
					Context.scrollBar->setVisible(true);
					Context.scrollBar->setPos(POWER_MAX - Context.GetPower( Station :: StationType :: Defence ));
					Context.selectedStation = 2;
					break;
				case KEY_KEY_3 :
					Context.scrollBar->setVisible(true);
					Context.scrollBar->setPos(POWER_MAX - Context.GetPower( Station :: StationType :: Navigation));
					Context.selectedStation = 3;
					break;
				case KEY_KEY_4 :
					Context.scrollBar->setVisible(true);
					Context.scrollBar->setPos(POWER_MAX - Context.GetPower( Station :: StationType :: Weapon ));
					Context.selectedStation = 4;
					break;
					
				}
				break;
			}
		}

		return false;
	}

private:
	UIData & Context;
};*/