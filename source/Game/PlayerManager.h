#ifndef PLAYER_MANAGER
#define PLAYER_MANAGER

#include "NetworkInterface.h"
#include "Irrlicht\irrlicht.h"
#include "PlayerData.h"
#include "Engine\INetworkListener.h"
#include "Engine\NetworkPacket.h"
#include "Stations\Station.h"

class PlayerManager : public INetworkListener
{
private:
	irr :: core :: map<int, PlayerData*>	*_serverPlayerData;
	PlayerData								*_localPlayerData;
	
	bool _isServer;

	//these are client side functions. 
	void RequestJoinServer( const wchar_t *player_name, int team_id, ENetPeer peer );
	void OnJoinAcceptedReceived( int player_player_id );
	void OnJoinDeniedReceived( );
	void OnLobbyStatusReceived( );

	//these are the server-side functions
	void OnClientJoinRequestReceived( const wchar_t *player_name, int team_id, ENetPeer peer );
	
public:
	PlayerManager( );
	~PlayerManager( );	

	void HandleNetworkMessage( NetworkPacket p );
	
	//this makes sure that the local data is sent to all the other players on the network (only local data)
	void SyncLocalPlayerData( StationType currentStation );
};
extern PlayerManager *player_manager;
#endif