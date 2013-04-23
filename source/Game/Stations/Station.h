#ifndef STATION_BASE
#define STATION_BASE
#pragma once

#include "..\Player.h"
#include "../../../include/Engine/Component.h"
#include "../../../include/Engine/Game.h"
#include "..\..\..\include\Engine\Network.h"

//TODO: When the NetworkInterface.h is ready, replace this code with the NetworkInterface
#include "..\..\..\include\Engine\INetworkListener.h"
#include "..\..\..\include\Engine\NetworkPacket.h"
#include "..\..\..\include\Engine\NetworkComponent.h"
#include "..\..\..\include\Engine\Networkable.h"
#include "..\..\..\include\Engine\Network.h"
//end TODO

#include "Irrlicht/irrlicht.h"

#ifdef ENTITY_SHIP
#include "..\Ship.h"
#endif

#define STUN_TIME 4.0
class Ship;
	
enum StationType
{
	ST_POWER		= 0,
	ST_DEFENCE		= 1,
	ST_WEAPON		= 2,
	ST_HELM		= 3,
	ST_NAVIGATION	= 4
};

class Station : public Component, public INetworkListener
{
public:
	Station( Ship *ship, int startHealth );
	Station( Ship *ship );
	virtual ~Station(void);

	virtual void DoCameraShake() = 0;

	StationType GetStationType( );

	bool HasPlayer( );
	bool IsPlayerPacketSender( NetworkPacket *p );
	bool SwitchTimePassed();
	
	bool getStationDestroyed();
	void setStationDestroyed(bool _destroyed);

	void update();

	virtual void HandleNetworkMessage( NetworkPacket packet ); // implement the interface method

protected:
	video::IVideoDriver *driver;

	Ship	*_ship;
	//Player	*_player;
	int		_playerID;

	time_t *_switchTime;			//the time that the player switched to this station.
	time_t *_playerOnStationTime;	//the time that the player has spent on this station (since he switched)
	//time_t *_stunTime;				//if a station fot stunned, the time it happened will be stored here.
	
	StationType _stationType;

	bool IsPacketForThisStation( sf :: Packet p );

	//when sending a packet to the server, we use this method
	void SendPacket( NetworkPacket *p, bool isReliable = true );
	//we also want to be able to subscribe all the stations to the information they need to receive. This is protected so all the individual stations can access it.
	void SubscribeForPacketType( PacketType t );
	//finally, we need to be able to unsubscribe for packets as well.
	void UnsubscribeForPacketType( PacketType t );

	NetworkPacket *PlayerEntersPacket( );
	NetworkPacket *PlayerLeavesPacket( );

private:	
	void OnPlayerEnters( );
	void OnPlayerLeaves( );
	bool _stationDestroyed;

public:
	void Initialize( int playerID );
	void DeInitialize( );
};
#endif