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
	irr :: core :: map<int, PlayerData> *_playerData;
	int									_localPlayer_id;
	
	void UpdatePlayer( int player_id, StationType type );
	//whenever the 
	void AddPlayerData( int player_id, const wchar_t *player_name, int team_id );
	void RemovePlayerData( int player_id );

	PlayerData *GetPlayerData( int player_id );
	
public:
	PlayerManager( );
	~PlayerManager( );	

	void HandleNetworkMessage( NetworkPacket p );
	void GenerateLocalPlayerData( int player_id, const wchar_t *name, int team_id );

	//this makes sure that the local data is sent to all the other players on the network (only local data)
	void SyncLocalPlayerData( );
};
extern PlayerManager *player_manager;
#endif