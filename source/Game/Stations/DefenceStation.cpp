#include "DefenceStation.h"


DefenceStation::DefenceStation(Core* core, Ship* ship) : Station(core, ship)
{
	this->_stationType = ST_DEFENCE;
	this->setStationDestroyed(false);
	std::srand((unsigned int)time(NULL));
}

DefenceStation::~DefenceStation()
{
	
}

void DefenceStation::Damage()
{
	
}

void DefenceStation::DoCameraShake()
{
	
} 


int DefenceStation :: GetDamage(StationType stationType)
{
	//Needs to return the DefenceStats data !!!!
	return 0;
}

void DefenceStation::OnEnabled(){

}

void DefenceStation::OnDisabled(){

}

void DefenceStation::enable() {
	(_ship)->help->setHelpText(L"todo: Exit station: 'Esc'");

	Station::enable();
}

void DefenceStation::disable()
{
	Station::disable();
}