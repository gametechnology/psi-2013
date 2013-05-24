#include "PlayerManager.h"
#include "Stations\Station.h"

PlayerManager *player_manager = new PlayerManager( );

PlayerManager :: PlayerManager( ) : INetworkListener( )
{
	if ( player_manager != NULL ) return;

	_isServer = Network :: GetInstance( ) -> IsServer( );
	//we want to receive messages when players are added, when they are updating their info and when they leave again
		
	if ( !Network :: GetInstance( ) -> IsServer( ) )
	{
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_JOIN_ACCEPTED, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_JOIN_DENIED, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_LOBBY_STATUS, this );
	} else
	{
		Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_JOIN_SERVER, this );
		this -> _serverPlayerData = new irr :: core :: map<int, PlayerData*>( );
	}
}

PlayerManager :: ~PlayerManager( )
{
	if ( !Network :: GetInstance( ) -> IsServer( ) )
	{
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_JOIN_ACCEPTED, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_JOIN_DENIED, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_LOBBY_STATUS, this );
	} else							 
		Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_JOIN_SERVER, this );
}

void PlayerManager :: OnClientJoinRequestReceived( const wchar_t *player_name, int team_id, ENetPeer peer )
{
	PlayerData *p = new PlayerData( );	
}

/**
* only when a player joins the already existing game, we will be inside this function.
*/
void PlayerManager :: RequestJoinServer( const wchar_t *player_name, int team_id, ENetPeer peer )
{
	if ( this -> _isServer ) return;
	//here, we received a message from a player that they want to join our game and they have sent some information regarding their data.
	this ->	_localPlayerData = new PlayerData( player_name, team_id, peer );
	//create a new packet that we are going to send to the server.
	NetworkPacket p = NetworkPacket( PacketType :: CLIENT_JOIN_SERVER );
	Network :: GetInstance( ) -> SendPacket( p, true );
}

/**
*In this method, we received a message from the server that we were able to join to the game. It also generates an id for us.
*/
void PlayerManager :: OnJoinAcceptedReceived( int player_id )
{
	//if this machine is flagged as server, we do nothing.
	if ( this -> _isServer ) return;
	//otherwise, we are going to set the player id in our local playerData.
	this ->	_localPlayerData -> id = player_id;
}

/**
*we should actually not get in this method, but it is nice to generate a nice message to the player that he could not join the game (if anything happens)
*/
void PlayerManager :: OnJoinDeniedReceived( )
{
	//do some error handing here (generate a message for the player)
}

void PlayerManager :: OnLobbyStatusReceived( )
{
	
}

/**
*here, the server will get a request that a player wants to join. So, he generates an ID and sends a successful join back (or a failed, if something went wrong)
*/
void PlayerManager :: OnClientJoinRequestReceived( const wchar_t *player_name, int team_id, ENetPeer peer )
{
	if ( !this -> _isServer ) return;
	//first, let's create a new PlayerData.
	PlayerData	*player_data = new PlayerData( player_name, team_id, peer );
	//we then continue to add it to our map of PlayerData's.
	this -> _serverPlayerData -> insert( player_data -> id, player_data );
	
	//then, we generate a new packet
	NetworkPacket packet = NetworkPacket( PacketType :: SERVER_JOIN_ACCEPTED );
	packet << player_data -> id;

	//and we send the packet back to the client
	//TODO: make sure that the packet is sent only to the client that requested the join.
	Network :: GetInstance( ) -> SendPacket( packet );
}

/*void PlayerManager :: UpdatePlayer( int player_id, StationType t )
{
	//here, we received a message that one of the players updated their data.
	//first, we get the PlayerData associated with the id we received
	PlayerData *player_data = GetPlayerData( player_id );
	player_data -> stationType	= t;	
	std :: cout << "Player: " << player_data -> name << "has entered the " << ( int ) t << " station.\n";
}

void PlayerManager :: AddPlayerData( int player_id, const wchar_t *player_name, int team_id )
{
	
	//and we add it to our _playerData map
	this -> _playerData -> insert( player_id, *player_data );
	std :: cout << "Added player: " << player_data -> name << " to the game. ID: " << player_data -> id << ". He is in team " << team_id << ".\n";
}*/

void PlayerManager :: RemovePlayerData( int player_id )
{
	//this player is removed and will never send updates again (the horror)
	this -> _playerData -> remove( player_id );
}

//handles all incoming messages of type Update player, remove player and add player
void PlayerManager :: HandleNetworkMessage( NetworkPacket packet )
{
	int			player_id;
	wstring		player_name;
	int			player_team_id;
	int			player_station_type;

	packet >> player_id;

	//we received a message. This contains a packet. First we check the packet type.
	switch ( packet.GetType( ) )
	{
	case PacketType :: CLIENT_ADD_PLAYER_DATA:
		packet >> player_name >> player_team_id;
		this -> AddPlayerData( player_id, player_name.c_str( ), player_team_id );
		break;

	case PacketType :: CLIENT_UPDATE_PLAYER_DATA:
		packet >> player_station_type;
		this -> UpdatePlayer( player_id, ( StationType ) player_station_type );
		break;

	case PacketType :: CLIENT_REMOVE_PLAYER_DATA:
		this -> RemovePlayerData( player_id );
		break;
	}
}

/*void PlayerManager :: GenerateLocalPlayerData( int player_id, const wchar_t *player_name, int team_id )
{
	PlayerData	*player_data = new PlayerData( player_id, player_name, team_id );
	this -> _playerData -> insert( player_id, *player_data );
	
	//TODO: check that this does not crash and burn
	wstring w = ( wstring ) player_name;
	//here we will send to all the other devices that we have generated a new player
	NetworkPacket p = NetworkPacket( PacketType :: CLIENT_ADD_PLAYER_DATA );
	p << player_id << w << team_id;

	//it is important that this message reaches all other devies, so we sent it reliably.
	Network :: GetInstance( ) -> SendPacket( p, true );
}

void PlayerManager :: SyncLocalPlayerData( StationType currentStation )
{
	//here, we sent our local data to the other players.
	this -> _localPlayerData -> stationType	= currentStation;
	//next, we create a packet where we place the data in from the player we got
	NetworkPacket	p = NetworkPacket( PacketType :: CLIENT_UPDATE_PLAYER_DATA );
	//place the values of the player_data in the packet
	p << player_data -> id << ( int ) player_data -> stationType;
	//and finally send the packet over the network to the other players.
	Network :: GetInstance( ) -> SendPacket( p, true );
}

PlayerData *PlayerManager :: GetPlayerData( int player_id )
{
	return &this -> _playerData -> find( player_id ) -> getValue( );
}*/