#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include "NetworkInterface.h"
#include "Irrlicht\irrlicht.h"
#include "PlayerData.h"
#include "Engine\INetworkListener.h"
#include "Engine\NetworkPacket.h"
#include "Stations\Station.h"
#include <time.h>

#pragma comment(lib, "winmm.lib")

class Game;

class PlayerManager : public INetworkListener
{
private:
	static PlayerManager*					_instance;
	irr :: core :: map<int, PlayerData*>	*_list_of_players;
	int										_local_player_id;
	
	int timeSent, timeTaken;
	int ticker;
	int lastId;
		
	PlayerManager( );

	int DistributeTeamId( );

	Game *game;

	//these are client side functions. 
	void OnClientJoinedGameReceived( int player_id, char *player_name, int team_id );
	void OnJoinDeniedReceived( );	
	
	//whenever something changes for any player, he will send something to the server.	

	//these are the server-side functions
	void OnClientJoinRequestReceived( char *player_name, ENetPeer peer );
	void OnClientStatusUpdateReceived( int player_id, CLIENT_STATUS_UPDATE update, int new_team_id );

	void PongReceived(int player_name, int timePingSend);
	void ServerSendPong(int player_name, int timePingSend);

public:
	static PlayerManager* GetInstance();
	~PlayerManager( );	

	void PingSend();
	void SetGame(Game *game);

	int getTimeTaken();

	void Init();
	void RequestJoinServer( char *player_name );
	void HandleNetworkMessage( NetworkPacket p );
	void UpdateClientStatus( CLIENT_STATUS_UPDATE update, int team_id );
	void SendPlayerInfoRequest();
	void StationUpdated( StationType stationType );
	//this makes sure that the local data is sent to all the other players on the network (only local data)
	void SyncLocalPlayerData( StationType currentStation );
	void ShowPlayerList( );
	PlayerData *GetLocalPlayerData( );
};
#endif