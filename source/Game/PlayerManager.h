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

class PlayerManager : public INetworkListener
{
private:
	static PlayerManager* _instance;
	irr :: core :: map<int, PlayerData*>	*_serverPlayerData;
	PlayerData								*_localPlayerData;
	
	bool _isServer;
	double timeSent, timeTaken;
	int ticker;
	
	PlayerManager( );

	//these are client side functions. 
	void OnJoinAcceptedReceived( int player_player_id );
	void OnJoinDeniedReceived( );
	//whenever something changes for any player, he will send something to the server.	

	//these are the server-side functions
	void OnClientJoinRequestReceived( char *player_name, int team_id, ENetPeer peer );
	void OnClientStatusUpdateReceived( int player_id, CLIENT_STATUS_UPDATE update, int new_team_id );

	void PongReceived(int player_name);
	void ServerSendPong(int player_name);

public:
	static PlayerManager* GetInstance();
	~PlayerManager( );	

	void PingSend();

	int getTimeTaken();

	void Init();
	void RequestJoinServer( char *player_name, int team_id );
	void HandleNetworkMessage( NetworkPacket p );
	void UpdateClientStatus( CLIENT_STATUS_UPDATE update, int team_id );
	void SendPlayerInfoRequest();
	void PlayerManager :: stationUpdated(StationType stationType);
	//this makes sure that the local data is sent to all the other players on the network (only local data)
	void SyncLocalPlayerData( StationType currentStation );
	void CheckInput( bool isDebugKeyPressed );
};
#endif