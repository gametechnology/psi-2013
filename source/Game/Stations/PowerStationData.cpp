#include "PowerStationData.h"

PowerStationData :: PowerStationData( )
{
	_stationsPowerUsage	= new irr::core::map<StationType, Station*>( );
	powerPool = POWER_MAX;
}

void PowerStationData :: SubscribeStation( Station *s )
{
	_stationsPowerUsage->insert(s->GetStationType(), s);
}

void PowerStationData :: UpdatePowerUsage(StationType s, int newValue, bool sentByServer = false)
{
	Station *station = _stationsPowerUsage->find(s)->getValue();

	int prevValue = station->getPower();
	powerPool += prevValue;

	//we want a value that is equal to or larger than 0, but smaller than or equal to the total amount of power.
	newValue = MIN_INT(MAX_INT(0, newValue), powerPool);

	powerPool -= newValue;
	_powerUsed = POWER_MAX - powerPool;
	
	station->updatePower(newValue);

	if(!sentByServer)
	{
		NetworkPacket packet(PacketType::CLIENT_POWER_CHANGED);
		packet << s;
		packet << newValue;
		Network::GetInstance()->SendPacket(packet, true);
	}
}

int PowerStationData :: GetPower(StationType s)
{	
	return _stationsPowerUsage->find(s)->getValue()->getPower();
}
