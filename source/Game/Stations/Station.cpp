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

bool Station :: SwitchTimePassed()
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
	when a player enters a station, that station will be initialized and updated
*/
void Station :: Initialize( int playerID )
{
	this -> _playerID					= playerID;
	
	if ( this -> _stationType != ST_POWER )		this -> _ship -> _powerStation		-> SubscribeStation( this );
	if ( this -> _stationType != ST_DEFENCE )	this -> _ship -> _defenceStation	-> SubscribeStation( this );

	//subscribe to the Networking protocol, that we want to subscribe to the player status changes packet type
	SubscribeForPacketType( PacketType :: CLIENT_STATION_PLAYER_ENTERS );

	OnPlayerEnters( );
}


void Station :: DeInitialize( )
{
	this -> _playerID					= -1;

	OnPlayerLeaves( );	
}

void Station :: OnPlayerEnters( )
{
	//set the time that the player entered the station ( or left )
	time( this -> _switchTime );

	//send a message to the server that the player entered of left.
	Network :: GetInstance( ) -> SendPacket( *PlayerEntersPacket( ) );
}

void Station :: OnPlayerLeaves( )
{
	
}

/**
	Creates and returns a packet thast should be sent when a player enters the station
*/
NetworkPacket *Station :: PlayerEntersPacket( )
{
	
	//we create a new packet to store our data in.
	sf :: Packet	packet	= sf :: Packet( );
		
	//then enter our information (player ID, station ID, ship ID and the time the player entered the ship). 
	//We cannot send a time_t, but we can convert it to an int
	packet << this -> _ship -> shipID << ( int ) this -> _stationType << this -> _playerID << ( int ) this -> _switchTime;

	//next, we create a network packet to store the packet inside.  
	NetworkPacket	*np		= new NetworkPacket( PacketType :: CLIENT_STATION_PLAYER_ENTERS, packet );

	//and return it
	return np;
}

NetworkPacket *Station :: PlayerLeavesPacket( )
{
	
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
	case PacketType :: CLIENT_STATION_PLAYER_ENTERS:
		//first, we are creating a temporary int for the stationID and shipID, because we need to take it from the packet
		int stationID;
		int shipID;
		int time;

		packet >> shipID >> stationID >> _playerID >> time;
		//we then take the time that the player entered the station and convert it back to a time_t object
		*this -> _switchTime = ( time_t ) time;
		break;
	case PacketType :: CLIENT_STATION_PLAYER_LEAVES:
		
		break;
	}
}

void Station :: SubscribeForPacketType( PacketType t )
{
	Network :: GetInstance( ) -> AddListener( t, this );
}

void Station :: UnsubscribeForPacketType( PacketType t )
{
	Network :: GetInstance( ) -> RemoveListener( t, this );
}