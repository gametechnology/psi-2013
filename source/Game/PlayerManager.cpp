#include "PlayerManager.h"
#include "Stations\Station.h"

PlayerManager *player_manager = new PlayerManager( );

PlayerManager :: PlayerManager( ) : INetworkListener( )
{
	if ( player_manager != NULL ) return;

	this -> _playerData = new irr :: core :: map<int, PlayerData>( );
	//we want to receive messages when players are added, when they are updating their info and when they leave again
	Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_ADD_PLAYER_DATA,	this );
	Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_UPDATE_PLAYER_DATA, this );
	Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_REMOVE_PLAYER_DATA, this );
	Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_ALL_PLAYERS, this);
	Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_GET_ALL_PLAYERS, this);
}

PlayerManager :: ~PlayerManager( )
{
	Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_ADD_PLAYER_DATA, this );
	Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_UPDATE_PLAYER_DATA, this );
	Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_REMOVE_PLAYER_DATA, this );
	Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_ALL_PLAYERS, this );
	Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_GET_ALL_PLAYERS, this );
}

PlayerData *PlayerManager :: GetLocalPlayerData( )
{
	return GetPlayerData( _localPlayer_id );
}

void PlayerManager:: SendPlayerInfoRequest()
{
	Network :: GetInstance() -> SendPacket(NetworkPacket(PacketType :: CLIENT_GET_ALL_PLAYERS));
}

void PlayerManager :: UpdatePlayer( int player_id, StationType t )
{
	//here, we received a message that one of the players updated their data.
	//first, we get the PlayerData associated with the id we received
	PlayerData *player_data = GetPlayerData( player_id );
	player_data -> stationType	= t;	
	std :: cout << "Player: " << player_data -> name << "has entered the " << ( int ) t << " station.\n";
}

void PlayerManager :: AddPlayerData( int player_id, const wchar_t *player_name, int team_id )
{
	//here, we received a message from a player that they want to join our game and they have sent some information regarding their data.
	PlayerData	*player_data = new PlayerData(player_name, team_id, );
	//and we add it to our _playerData map
	this -> _playerData -> insert( player_id, *player_data );
	std :: cout << "Added player: " << player_data -> name << " to the game. ID: " << player_data -> id << ". He is in team " << team_id << ".\n";
}

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
	wstring		allPlayersMessage;
	int			player_team_id;
	int			player_station_type;

	//we received a message. This contains a packet. First we check the packet type.
	switch ( packet.GetType( ) )
	{
	case PacketType :: CLIENT_ADD_PLAYER_DATA:
		packet >> player_id;
		packet >> player_name >> player_team_id;
		this -> AddPlayerData( player_id, player_name.c_str( ), player_team_id );
		break;

	case PacketType :: CLIENT_UPDATE_PLAYER_DATA:
		packet >> player_id;
		packet >> player_station_type;
		this -> UpdatePlayer( player_id, ( StationType ) player_station_type );
		break;

	case PacketType :: CLIENT_REMOVE_PLAYER_DATA:
		packet >> player_id;
		this -> RemovePlayerData( player_id );
		break;

	case PacketType ::SERVER_ALL_PLAYERS:
		packet >> allPlayersMessage;
		cout << "\nAll Player Message: \n" << allPlayersMessage.c_str() << endl;
		break;
	}
}

void PlayerManager :: GenerateLocalPlayerData( int player_id, const wchar_t *player_name, int team_id )
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
	//first, we have to get the playerdata of the local player
	PlayerData *player_data = GetPlayerData( this -> _localPlayer_id );
	player_data -> stationType	= currentStation;
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
}