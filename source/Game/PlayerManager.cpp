#include "PlayerManager.h"
#include "Stations\Station.h"

PlayerManager *player_manager	= new PlayerManager( );
int PlayerData :: uniqueId		= 0;

PlayerManager :: PlayerManager( ) : INetworkListener( )
{
	if ( player_manager != NULL ) return;
	
	this -> _serverPlayerData = new irr :: core :: map<int, PlayerData*>( );
	//set the unique ID of the playerData's to be 0.
	
	if ( this -> _isServer )
	{
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_REQUEST_ACCEPTED, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_REQUEST_DENIED, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_LOBBY_STATUS, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_ALL_PLAYERS, this );
	} else
	{
		Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_REQUEST_JOIN_SERVER, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_GET_ALL_PLAYERS, this);
	}
	//we want to receive messages when players are added, when they are updating their info and when they leave again
}

PlayerManager :: ~PlayerManager( )
{
	if ( this -> _isServer )
	{
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_ALL_PLAYERS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_REQUEST_DENIED, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_LOBBY_STATUS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_ALL_PLAYERS, this );
	} else
	{
		Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_GET_ALL_PLAYERS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_REQUEST_JOIN_SERVER, this );
	}
	//delete all the other crap.
}

/**
*here, we received a message from the client, stating that their information has changed (changed team, left game )
*/
void PlayerManager :: UpdateClientStatus( CLIENT_STATUS_UPDATE update, int team_id )
{
	//if we are the server, we will only update our local info.
	if ( !this -> _isServer )	return;
	
	//we create a new packet.
	NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_UPDATE_LOBBY_STATUS );
	//first add the id, then what type of update we want to perform.
	packet << _localPlayerData -> id << update << team_id; 

	Network :: GetInstance( ) -> SendPacket( packet, true );
}

/**
* only when a player joins the already existing game, we will be inside this function.
*/
void PlayerManager :: RequestJoinServer( const wchar_t *player_name, int team_id )
{
	cout << "I would like to join this game.\n";
	//here, we received a message from a player that they want to join our game and they have sent some information regarding their data.
	this ->	_localPlayerData = new PlayerData( player_name, team_id );
	this -> _isServer = Network :: GetInstance( ) -> IsServer( );

	if ( this -> _isServer ) return;
	//create a new packet that we are going to send to the server.
	NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_REQUEST_JOIN_SERVER );	
	packet << ( wstring ) player_name << team_id;
	Network :: GetInstance( ) -> SendPacket( packet, true );
}

/**
*here, the server receives a request from a client.
*/
void PlayerManager :: OnClientJoinRequestReceived( const wchar_t *player_name, int team_id, ENetPeer peer )
{
	cout << "I received a message from player " << *player_name << " that he would like to join.\n";
	//if this is not the server, we do nothing. This is not a message for us.
	if ( !this -> _isServer )	return;
	//create a new PlayerData.
	PlayerData *p = new PlayerData( player_name, team_id, &peer );
	//and add it to our list of playerData's
	this -> _serverPlayerData -> insert( p -> id, p );

	//then, we generate a new packet
	NetworkPacket packet = NetworkPacket( PacketType :: SERVER_REQUEST_ACCEPTED );
	packet << p -> id;

	//and we send the packet back to the client (and only to that client, the rest of the clients do not need to know abot ths message)
	Network :: GetInstance( ) -> SendServerPacket( packet, &peer, true );


	//TODO: sort of error handling when things go wrong and send a CLIENT_REQUEST_DENIED packet	
}

/**
*In this method, we received a message from the server that we were able to join to the game. It also generates an id for us.
*/
void PlayerManager :: OnJoinAcceptedReceived( int player_id )
{
	cout << "Yay! I now am in the game. this is my id: " << player_id;
	//if this machine is flagged as server, we do nothing.
	if ( this -> _isServer ) return;
	//otherwise, we are going to set the player id in our local playerData.
	this ->	_localPlayerData -> id = player_id;
}

void PlayerManager :: OnClientStatusUpdateReceived( int player_id, CLIENT_STATUS_UPDATE update, int new_team_id )
{
	if ( !this -> _isServer ) return;
	switch( update )
	{
	case CLIENT_STATUS_UPDATE :: CHANGED_TEAM:
		this -> _serverPlayerData -> find( player_id ) -> getValue( ) -> team_id = new_team_id;
		break;

	case CLIENT_STATUS_UPDATE :: LEFT_GAME:
		//we now remove it from the map.
		this -> _serverPlayerData -> remove( player_id );
	}
}

/**
*if anything went wrong server side we can let the user know.
*/
void PlayerManager :: OnJoinDeniedReceived( )
{
	//TODO: Some shit.
}

void PlayerManager :: CheckInput( bool isDebugKeyPressed )
{
	if ( isDebugKeyPressed )
	{
		cout << "name: " << _localPlayerData -> name << ":\n";
		cout << "\tID: " << _localPlayerData -> id << "\n";
		cout << "\tteam_id: " << _localPlayerData -> team_id << "\n";
		//cout << "\tip address: " << _localPlayerData -> peer -> ( int ) outgoingPeerID << "\n";
		cout << "\tstation type: " << _localPlayerData -> stationType << "\n";
	}
}

/*void PlayerManager :: OnLobbyStatusReceived( int player_id, int team_id )
{
	//we got a message from a client that their information changed.
}*/

void PlayerManager:: SendPlayerInfoRequest()
{
	Network :: GetInstance( ) -> SendPacket( NetworkPacket(PacketType :: CLIENT_GET_ALL_PLAYERS) );
}

//handles all incoming messages of type Update player, remove player and add player
void PlayerManager :: HandleNetworkMessage( NetworkPacket packet )
{
	int			player_id;
	wstring		player_name;
	wstring		allPlayersMessage;
	int			player_team_id = -1;
	int			player_station_type;

	int			update;
	
	//first, we get the player_id	
	switch ( packet.GetType( ) )
	{
	case PacketType :: CLIENT_REQUEST_JOIN_SERVER:

		packet >> player_name >> player_team_id;

		//we need to know the peer of the player. We reconstruct it using it's host and port numbers.
		this -> OnClientJoinRequestReceived( player_name.c_str( ), player_team_id, packet.GetSender( ) );
		break;

	case PacketType :: SERVER_REQUEST_ACCEPTED:

		packet >> player_id;
		this -> OnJoinAcceptedReceived( player_id );
		break;

	case PacketType :: SERVER_REQUEST_DENIED:

		this -> OnJoinDeniedReceived( );
		break;

	case PacketType :: CLIENT_UPDATE_LOBBY_STATUS:

		packet >> player_id >> update >> player_team_id;
		this -> OnClientStatusUpdateReceived( player_id, ( CLIENT_STATUS_UPDATE ) update, player_team_id );

	case PacketType :: SERVER_ALL_PLAYERS:
		packet >> allPlayersMessage;
		cout << "\nAll Player Message: \n" << allPlayersMessage.c_str() << endl;
		break;
	}
}