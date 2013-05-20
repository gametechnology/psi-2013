#include "DefenceStation.h"
#include "Station.h"
#include "..\Ship.h"

DefenceStation::DefenceStation(Ship* ship) : Station(ship)
{
	this->_stationType	= ST_DEFENCE;
	//this->_stations		= new irr::core::map<StationType, DefenceStation::DefenceStats>();
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