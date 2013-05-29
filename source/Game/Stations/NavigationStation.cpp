#include "NavigationStation.h"

NavigationStation::NavigationStation(Core* core, Ship *ship) : Station(core, ship)
{
	this->_stationType = ST_NAVIGATION;
	this -> setStationDestroyed(false);
}

NavigationStation :: ~NavigationStation()
{

}

void NavigationStation :: DoCameraShake( )
{
	
}

void NavigationStation :: OnEnabled(){

}

void NavigationStation :: OnDisabled(){

}

void NavigationStation::enable() {
	(_ship)->help->setHelpText(L"todo: Exit station: 'Esc'");

	Station::enable();
}

void NavigationStation::disable()
{
	Station::disable();
}