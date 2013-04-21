#include "HelmStation.h"

HelmStation :: HelmStation(Ship *ship) : Station( ship )
{
	this->_stationType = ST_HELM;
	this -> setStationDestroyed(false);
}

HelmStation :: ~HelmStation( )
{
	
}

void HelmStation :: DoCameraShake( )
{
	
}

void HelmStation :: HandleNetworkMessage( NetworkPacket p )
{		
	sf :: Packet packet = p.GetPacket( );
	switch( p.GetPacketType( ) )
	{
	case PacketType :: CLIENT_HELM_STATION_USER_INPUT:
		if ( IsPacketForThisStation( packet ) )
		{
			
		}
		break;
	default:
		Station :: HandleNetworkMessage( p );
	}	
}