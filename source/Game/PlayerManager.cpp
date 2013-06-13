#include "MainMenuScene.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Ship.h"

int PlayerData :: uniqueId				= 1;
PlayerManager* PlayerManager::_instance = 0;
char *localName = new char;
bool isDisconnected = false;

PlayerManager :: PlayerManager( ) : INetworkListener( )
{
	timeTaken = 0;
	lastId = 2;
}

PlayerManager* PlayerManager::GetInstance()
{
	if(_instance == 0)
	{
		_instance = new PlayerManager();
		_instance->ticker = 0;
		_instance->timeSent = 0;
	}

	return _instance;
}

int PlayerManager::DistributeTeamId(){
	if (lastId==1){
		lastId=2;
	}else{
		lastId=1;
	}
	return lastId;
}

void PlayerManager::Init( )
{
	this -> _list_of_players = new irr :: core :: map<int, PlayerData*>( );
	//set the unique ID of the playerData's to be 0.
	
	if ( !Network :: GetInstance( ) -> IsServer( ) )
	{
		//As a client I listen to:
		cout << endl << endl << endl << "I am a client!" << endl << endl;
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_REQUEST_ACCEPTED, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_REQUEST_DENIED, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_LOBBY_STATUS, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_ALL_PLAYERS, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_PONG, this );
	} 
	else
	{
		//As a server I listexn to:
		cout << endl << endl << endl << "I am a server!" << endl << endl;
		Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_REQUEST_JOIN_SERVER, this );
		Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_GET_ALL_PLAYERS, this);
		Network :: GetInstance( ) -> AddListener( PacketType :: CLIENT_PING, this);
		Network :: GetInstance( ) -> AddListener( PacketType :: SERVER_PONG, this);
	}
	//we want to receive messages when players are added, when they are updating their info and when they leave again
}

PlayerManager :: ~PlayerManager( )
{
	if ( !Network :: GetInstance( ) -> IsServer( ) )
	{
		//As a client stop listening to:
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_ALL_PLAYERS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_REQUEST_DENIED, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_LOBBY_STATUS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_ALL_PLAYERS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_PONG, this );
	} 
	else
	{
		//As a server stop listining to:
		Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_GET_ALL_PLAYERS, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_REQUEST_JOIN_SERVER, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: CLIENT_PING, this );
		Network :: GetInstance( ) -> RemoveListener( PacketType :: SERVER_PONG, this );
	}
	//delete all the other crap.
}
void PlayerManager :: StationUpdated( StationType stationType )
{
	this -> GetLocalPlayerData( ) -> stationType = stationType;
}

/**
*here, we received a message from the client, stating that their information has changed (changed team, left game )
*/
void PlayerManager :: UpdateClientStatus( CLIENT_STATUS_UPDATE update, int team_id )
{	
	//we create a new packet.
	NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_UPDATE_LOBBY_STATUS );
	//first add the id, then what type of update we want to perform.
	packet << this -> _local_player_id << update << team_id; 

	Network :: GetInstance( ) -> SendPacket( packet, true );
}

int PlayerManager :: getTimeTaken( )
{	
	return timeTaken;
}

/**
* only when a player joins the already existing game, we will be inside this function.
*/
void PlayerManager :: RequestJoinServer( char *player_name )
{
	localName	= player_name;
	cout << "I would like to join this game. My name is: " << player_name <<"\n";
	//here, we received a message from a player that they want to join our game and they have sent some information regarding their data.
			
	//create a new packet that we are going to send to the server.
	NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_REQUEST_JOIN_SERVER );
	packet << player_name;
	Network :: GetInstance( ) -> SendPacket( packet, true );

	if ( Network :: GetInstance( ) -> IsServer( ) )
	{
		this -> _local_player_id = 1;
	}
}

PlayerData *PlayerManager :: GetLocalPlayerData( )
{
	return this -> _list_of_players -> find( this -> _local_player_id ) -> getValue( );
}

/**
*here, the server receives a request from a client.
*/
void PlayerManager :: OnClientJoinRequestReceived( char *player_name, ENetPeer peer )
{
	std :: cout << "I received a message from player " << player_name << " that he would like to join.\n";

	int team_id = DistributeTeamId();
	//if this is not the server, we do nothing. This is not a message for us.
	//create a new PlayerData.
	PlayerData *p = new PlayerData( player_name, team_id );
	//and add it to our list of playerData's
	this -> _list_of_players -> insert( p -> id, p );

	//then, we generate a new packet for that specific client. 
	NetworkPacket packet = NetworkPacket( PacketType :: SERVER_REQUEST_ACCEPTED );
	packet << player_name << p -> id << p -> team_id;

	//and we send the packet back to the client (and only to that client, the rest of the clients do not need to know abot ths message)
	Network :: GetInstance( ) -> SendServerPacket( packet, true );
	
	//we now create a new packet that the server will send to all the clients. They should add the server as well.
	NetworkPacket server_player_data_packet = NetworkPacket( PacketType :: SERVER_REQUEST_ACCEPTED );
	//find the local player (which is the server).
	PlayerData *server_player_data = GetLocalPlayerData( );
	//extract the data from the server player
	server_player_data_packet << server_player_data -> name << server_player_data -> id << server_player_data -> team_id;

	Network :: GetInstance( ) -> SendServerPacket( server_player_data_packet, true );
}

/**
*In this method, we received a message from the server that we were able to join to the game. If the player is the player that sent the request (AKA, this local user)
*then we set the local_player_id. We then continue to add it to our dictionary.
*/
void PlayerManager :: OnClientJoinedGameReceived( int player_id, char *player_name, int player_team_id )
{
	//otherwise, we are going to set the player id in our local playerData.
	//if this new player is not already in the list of players, we insert it in the list
	if ( this -> _list_of_players -> find( player_id ) == NULL )
	{
		cout << "Yay! I now am in the game. this is my id: " << player_id << endl;
		this -> _list_of_players -> insert( player_id, new PlayerData( player_name, player_team_id, player_id ) );
	}
}

void PlayerManager :: OnClientStatusUpdateReceived( int player_id, CLIENT_STATUS_UPDATE update, int new_team_id )
{
	if ( !Network :: GetInstance( ) -> IsServer( ) ) return;
	switch( update )
	{
	case CLIENT_STATUS_UPDATE :: CHANGED_TEAM:
		this -> _list_of_players -> find( player_id ) -> getValue( ) -> team_id = new_team_id;
		break;

	case CLIENT_STATUS_UPDATE :: LEFT_GAME:
		//we now remove it from the map.
		this -> _list_of_players -> remove( player_id );
	}
}

/**
*if anything went wrong server side we can let the user know.
*/
void PlayerManager :: OnJoinDeniedReceived( )
{
	//TODO: Some shit.
}

void PlayerManager :: ShowPlayerList( )
{
	int size	= this -> _list_of_players -> size( ) + 1;
	for ( int i = 1; i < size; i++ )
	{
		std :: cout << *this -> _list_of_players -> find( i ) -> getValue( ) << std :: endl;
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
	int			timePingSent;
	int			player_team_id = -1;
	int			player_station_type;
	int			update;
	char		*player_name = new char;
	wstring		allPlayersMessage;
	
	//first, we get the player_id	
	switch ( packet.GetType( ) )
	{
	case PacketType :: CLIENT_REQUEST_JOIN_SERVER:

		packet >> player_name;

		//we need to know the peer of the player. We reconstruct it using it's host and port numbers.
		this -> OnClientJoinRequestReceived( player_name, packet.GetSender( ) );
		break;

	case PacketType :: SERVER_REQUEST_ACCEPTED:
		packet >> player_name >> player_id >> player_team_id;
		
		std :: cout << "I received a message from the server, with player_id: " << player_id <<" and team id is: "<< player_team_id << endl;
		if ( strcmp( player_name, localName ) == 0 )
		{
			std :: cout << player_name << " would like to join";
			this -> _local_player_id = player_id;
		}
		std :: cout << "_local_player_id set to " << player_id << endl;
		this -> OnClientJoinedGameReceived( player_id, player_name, player_team_id );
		break;

	case PacketType :: SERVER_REQUEST_DENIED:

		this -> OnJoinDeniedReceived( );
		break;
	case PacketType :: CLIENT_UPDATE_LOBBY_STATUS:
			packet >> player_id >> update >> player_team_id;
			this -> OnClientStatusUpdateReceived( player_id, ( CLIENT_STATUS_UPDATE ) update, player_team_id );
		break;
	case PacketType :: SERVER_ALL_PLAYERS:
		packet >> allPlayersMessage;
		cout << "\nAll Player Message: \n" << allPlayersMessage.c_str() << endl;
		break;

	case PacketType :: SERVER_PONG:
		packet >> player_id;
		packet >> timePingSent;
		PongReceived(player_id, timePingSent);
		break;
	case PacketType :: CLIENT_PING:
		packet >> player_id;
		packet >> timePingSent;
		ServerSendPong(player_id, timePingSent);
		break;
	}
}

void PlayerManager :: SetGame(Game* game)
{
	this->game = game;
}

void PlayerManager :: PingSend()
{
	 ticker++;

	 if (timeSent == 0 && ticker >= 500)
	 {
		  cout << "CLIENT: Ping send to the server from player-" << this -> GetLocalPlayerData( ) -> id << "("<< this -> GetLocalPlayerData( ) -> name <<") !" << endl;
		  ticker = 0;
		  timeSent = timeGetTime();
		  isDisconnected = false;

		  NetworkPacket packet = NetworkPacket(PacketType::CLIENT_PING);
		  packet << this -> GetLocalPlayerData( ) -> id;
		  packet << (int) timeGetTime();
		  Network :: GetInstance() -> SendPacket(packet, true);
		  cout << "CLIENT: Ping send to the server from player-" << this -> GetLocalPlayerData( ) -> id << "("<< this -> GetLocalPlayerData( ) -> name <<") !" << endl;
	 }
	 else if (ticker >= 1000 && !isDisconnected)
	 {	
		 isDisconnected = true;
		 cout << endl <<"CLIENT: I am disconnected!" << endl;
		 game->device->closeDevice();
	 }
}

void PlayerManager :: PongReceived(int player_id, int timePingSent)
{
	if (player_id != this -> GetLocalPlayerData( ) -> id)
		return;

	timeTaken = timeGetTime() - timePingSent;
	cout << "CLIENT: Pong received from server by player-" << this -> GetLocalPlayerData( ) -> id << "("<< this -> GetLocalPlayerData( ) -> name <<")!" << endl;
	cout << "CLIENT: " << timeTaken << " ms!" << endl << endl;

	timeSent = 0;
}

void PlayerManager :: ServerSendPong(int player_id, int timePingSent)
{
	cout << "SERVER: Ping received from player-" << player_id << endl; 
	cout << "SERVER: Sending back Pong[id=" << player_id << ", time=" << timePingSent << "]" << endl;
	
	NetworkPacket nwp = NetworkPacket(PacketType::SERVER_PONG);
	nwp << player_id;
	nwp << timePingSent;
	
    Network ::GetInstance()->SendPacket(nwp);
    Network ::GetInstance()->SendServerPacket(nwp);
}