#include "Station.h"
#include "PowerStation.h"
#include "DefenceStation.h"


Station :: Station( Ship *ship, int startHealth ) : Component( ship )
{
	driver = Game :: driver;
	this ->	_ship	= ship;
	
}

Station :: Station( Ship * ship ) : Component(ship)
{
	this -> _ship   = ship;	
}

Station :: ~Station( void )
{
	//delete _ship;
	//delete _player;
	//delete _switchTime;
	//delete _playerOnStationTime;
	//delete _stunTime;
}

bool Station :: HasPlayer( )
{
	return this -> _playerID > -1;
}

//when we receive a packet, we only want to update the 
bool Station :: IsPlayerPacketSender( NetworkPacket *p )
{
	int playerID;
	p -> GetPacket( ) >> playerID;
	return HasPlayer( ) || playerID != this -> _playerID;
}

bool Station::SwitchTimePassed()
{
	return this -> _playerOnStationTime > this -> _switchTime;
}

StationType Station :: GetStationType( )
{
	return this -> _stationType;
}

void Station :: update( )
{
	Component :: update( );
	
	//Update Stun Time
	//Update player on station time	
}

bool Station::getStationDestroyed( )
{
	return this -> _stationDestroyed;
}

void Station :: setStationDestroyed(bool _destroyed)
{
	this -> _stationDestroyed = _destroyed;
}

/**
	when a player enters a station, that station will be initialized and the updated
*/
void Station :: Initialize( int playerID )
{
	this -> _switchTime = new time_t( );
	this -> _playerID					= playerID;		 
	
	if ( this -> _stationType != ST_POWER )		this -> _ship -> _powerStation		-> SubscribeStation( this );
	if ( this -> _stationType != ST_DEFENCE )	this -> _ship -> _defenceStation	-> SubscribeStation( this );

	//subscribe to the Networking protocol, that we want to subscribe to the player status changes packet type
	SubscribeForPacketType( PacketType :: CLIENT_STATION_PLAYER_STATUS_CHANGED );

	OnPlayerEntersOrLeaves( );
}


void Station :: DeInitialize( )
{
	this -> _playerID					= -1;

	OnPlayerEntersOrLeaves( );
}

void Station :: OnPlayerEntersOrLeaves( )
{
	
}

/**
	Creates and returns a packet thast should be sent when a player enters the station
*/
NetworkPacket *Station :: PlayerEntersOrLeavesPacket( )
{
	//we create a new packet to store our data in.
	sf :: Packet	packet	= sf :: Packet( );
		
	//then enter our information (player ID, station ID, ship ID and the time the player entered the ship)
	packet << this -> _ship -> shipID << ( int ) this -> _stationType << this -> _playerID << this -> _switchTime;

	//next, we create a network packet to store the packet inside.  
	NetworkPacket	*np		= new NetworkPacket( PacketType :: CLIENT_STATION_PLAYER_STATUS_CHANGED, packet );

	//and return it
	return np;
}

bool Station :: IsPacketForThisStation( sf :: Packet p )
{
	int shipID;
	int stationType;
	p >> shipID >> stationType;

	return stationType == ( int ) this -> _stationType && shipID == this -> _ship -> shipID;
}

void Station :: HandleNetworkMessage( NetworkPacket p )
{
	sf :: Packet packet = p.GetPacket( );

	switch( p.GetPacketType( ) )
	{
	case PacketType :: CLIENT_STATION_PLAYER_STATUS_CHANGED:
		//first, we are creating a temporary int for the stationID, because we need to remove it from the 
		int stationID;
		int shipID;
		packet >> shipID >> stationID >> this -> _playerID;
		packet >> ( int )( this -> _switchTime );
		break;	
	}
}

void Station :: SubscribeForPacketType( PacketType t )
{
	Network :: GetInstance( ) -> AddListener( t, this );
}

