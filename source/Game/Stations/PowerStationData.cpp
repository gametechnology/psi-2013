#include "PowerStationData.h"

PowerStationData :: PowerStationData( )
{
	this -> _stationsPowerUsage	= new irr::core::map<StationType, Station*>( );
	this -> powerPool	= POWER_MAX;
}

void PowerStationData :: SubscribeStation( Station *s )
{
	this -> _stationsPowerUsage	-> insert( s -> GetStationType( ), s );
}

void PowerStationData :: UpdatePowerUsage(StationType s, int newValue, bool sentByServer )
{
	Station *station = this -> _stationsPowerUsage -> find( s ) -> getValue();

	int prevValue		= station->getPower();
	powerPool			+= prevValue;

	//we want a value that is equal to or larger than 0, but smaller than or equal to the total amount of power.
	newValue			= MIN_INT( MAX_INT( 0, newValue ), powerPool );

	this -> powerPool	-= newValue;
	this -> _powerUsed	=  POWER_MAX - this -> powerPool;
	
	station->updatePower(newValue);

	if(!sentByServer)
	{
		NetworkPacket packet(PacketType::CLIENT_POWER_CHANGED);
		packet << s;
		packet << newValue;
		Network::GetInstance()->SendPacket(packet, true);
	}

}

int PowerStationData :: GetPower(StationType s )
{
	
	return this -> _stationsPowerUsage -> find( s ) -> getValue( )->getPower();
}
