#include "PlayerManager.h"
#include "Player.h"
#include "Ship.h"

int PlayerData :: uniqueId		= 1;
PlayerManager* PlayerManager::_instance = 0;
char *localName = new char;

PlayerManager :: PlayerManager( ) : INetworkListener( )
{
	timeTaken = 0;
}

PlayerManager* PlayerManager::GetInstance()
{
	if(_instance == 0)
	{
		_instance = new PlayerManager();
		_instance->ticker = 0;
	}

	return _instance;
}

void PlayerManager::Init()
{
	this -> _serverPlayerData = new irr :: core :: map<int, PlayerData*>( );
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
		//As a server I listen to:
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
void PlayerManager :: stationUpdated(StationType stationType){
	_localPlayerData ->stationType = stationType;
}

/**
*here, we received a message from the client, stating that their information has changed (changed team, left game )
*/
void PlayerManager :: UpdateClientStatus( CLIENT_STATUS_UPDATE update, int team_id )
{
	
	//we create a new packet.
	NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_UPDATE_LOBBY_STATUS );
	//first add the id, then what type of update we want to perform.
	packet << _localPlayerData -> id << update << team_id; 

	Network :: GetInstance( ) -> SendPacket( packet, true );
}

int PlayerManager :: getTimeTaken()
{	
	return timeTaken;
}

/**
* only when a player joins the already existing game, we will be inside this function.
*/
void PlayerManager :: RequestJoinServer( char *player_name, int team_id )
{
	cout << "I would like to join this game. My name is: " <<player_name <<"\n";
	//here, we received a message from a player that they want to join our game and they have sent some information regarding their data.
	localName = player_name;
	
	this ->	_localPlayerData = new PlayerData( player_name, team_id );
	
	//create a new packet that we are going to send to the server.
	NetworkPacket packet = NetworkPacket( PacketType :: CLIENT_REQUEST_JOIN_SERVER );	
	packet << player_name << team_id;
	Network :: GetInstance( ) -> SendPacket( packet, true );
}

/**
*here, the server receives a request from a client.
*/
void PlayerManager :: OnClientJoinRequestReceived( char *player_name, int team_id, ENetPeer peer )
{
	cout << "I received a message from player " << player_name << " that he would like to join.\n";
	//if this is not the server, we do nothing. This is not a message for us.
	//create a new PlayerData.
	PlayerData *p = new PlayerData( player_name, team_id, peer );
	//and add it to our list of playerData's
	this -> _serverPlayerData -> insert( p -> id, p );

	//then, we generate a new packet
	NetworkPacket packet = NetworkPacket( PacketType :: SERVER_REQUEST_ACCEPTED );
	packet << player_name << p -> id ;

	//and we send the packet back to the client (and only to that client, the rest of the clients do not need to know abot ths message)
	Network :: GetInstance( ) -> SendServerPacket( packet, true );
	//Network :: GetInstance( ) -> SendPacket( packet, true );
	//TODO: sort of error handling when things go wrong and send a CLIENT_REQUEST_DENIED packet	
}

/**
*In this method, we received a message from the server that we were able to join to the game. It also generates an id for us.
*/
void PlayerManager :: OnJoinAcceptedReceived( int player_id )
{
	cout << "Yay! I now am in the game. this is my id: " << player_id << endl;
	//if this machine is flagged as server, we do nothing.
	//otherwise, we are going to set the player id in our local playerData.
	this ->	_localPlayerData -> id = player_id;
}

void PlayerManager :: OnClientStatusUpdateReceived( int player_id, CLIENT_STATUS_UPDATE update, int new_team_id )
{
	if ( !Network :: GetInstance( ) -> IsServer( ) ) return;
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
{	const char *stationInfo;
	if ( isDebugKeyPressed )
	{
		switch ( _localPlayerData -> stationType ) {
			case -1:
				stationInfo = "Hallway";
				break;
			case 0:
				stationInfo = "Power Station";
				break;
			case 1:
				stationInfo = "Defence Station";
				break;
			case 2:
				stationInfo = "Weapon Station";
				break;
			case 3:
				stationInfo = "Helm Station";
				break;
			case 4:
				stationInfo = "Navigation Station";
				break;
		}



		cout << "name: " << _localPlayerData -> name << ":\n";
		cout << "\tID: " << _localPlayerData -> id << "\n";
		cout << "\tteam_id: " << _localPlayerData -> team_id << "\n";
		//cout << "\tip address: " << _localPlayerData -> peer -> ( int ) outgoingPeerID << "\n";
		cout << "\tstation type: " << stationInfo << "\n";
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
	int			player_team_id = -1;
	int			player_station_type;
	int			update;
	char		*player_name = new char;
	wstring		allPlayersMessage;
	
	//first, we get the player_id	
	switch ( packet.GetType( ) )
	{
	case PacketType :: CLIENT_REQUEST_JOIN_SERVER:

		packet >> player_name >> player_team_id;

		//we need to know the peer of the player. We reconstruct it using it's host and port numbers.
		this -> OnClientJoinRequestReceived( player_name, player_team_id, packet.GetSender( ) );
		break;

	case PacketType :: SERVER_REQUEST_ACCEPTED:
		packet >> player_name;
		if ( *localName == *player_name){
		packet >> player_id;
		this -> OnJoinAcceptedReceived( player_id );
		}
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
		PongReceived(player_id);
		break;
	case PacketType :: CLIENT_PING:
		packet >> player_id;
		ServerSendPong(player_id);
		break;
	}
}

void PlayerManager :: PingSend()
{
	 ticker++;

	 if (ticker >= 500)
	 {
		  
		  timeSent = timeGetTime();

		  NetworkPacket packet = NetworkPacket(PacketType::CLIENT_PING);
		  packet << _localPlayerData->id;
		  Network :: GetInstance() -> SendPacket(packet, true);
		  cout << "CLIENT: Ping send to the server from player-" << _localPlayerData->id << "("<< _localPlayerData->name <<") !" << endl;
		  ticker = 0;
	 }
}

void PlayerManager :: PongReceived(int player_id)
{
	if (player_id != _localPlayerData->id)
		return;

	timeTaken = timeGetTime() - timeSent;
	cout << "CLIENT: Pong received from server by player-" << _localPlayerData->id << "("<< _localPlayerData->name <<")!" << endl;
	cout << "CLIENT: PingPong Time : " << timeTaken << " ms!" << endl << endl;
}

void PlayerManager :: ServerSendPong(int player_id)
{
	cout << "SERVER: Ping received from player-" << player_id << ", sending back Pong" << endl;
	NetworkPacket nwp = NetworkPacket(PacketType::SERVER_PONG);
	nwp << player_id;
	
	Network ::GetInstance()->SendServerPacket(nwp);
    Network ::GetInstance()->SendPacket(nwp);
}