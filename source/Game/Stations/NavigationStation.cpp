#include "NavigationStation.h"

NavigationStation::NavigationStation(Core* core, Interface* ui, Ship *ship) : Station(core, ui, ship)
{
	_stationType = ST_NAVIGATION;
	setStationDestroyed(false);
	_navCamera = NULL;
}

NavigationStation :: ~NavigationStation()
{

}

void NavigationStation :: DoCameraShake( )
{
	
}

void NavigationStation::enable() {
	(_ship)->help->setHelpText(L"todo: Exit station: 'Esc'");
		
	_navCamera = new CameraComponent(_core->getSmgr(), CameraComponent::FIRST_PERSON);
	_navCamera->init();

	_core->getActiveScene()->addComponent(_navCamera);
	
	Station::enable();
}

void NavigationStation::disable()
{
	if(_navCamera != NULL)
		delete _navCamera;

	Station::disable();
}