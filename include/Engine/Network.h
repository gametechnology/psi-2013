#ifndef NETWORK
#define NETWORK

#include "Engine\INetworkListener.h"
#include <enet\enet.h>
#include <list>

// forward declare NetworkPacket to prevent circular dependancy
class NetworkPacket;

enum PacketType
{
	CLIENT_JOIN = 0,
	CLIENT_QUIT,
	CLIENT_JOIN_TEAM,
	SERVER_WELCOMES,
	SERVER_REJECTS,

	//Add new PacketTypes above
	LAST_TYPE
};

class Network
{
private:
	const int _port;

	Network();
	
	bool _isServer;
	bool _isConnected;
	static Network* instance;
	std::list<INetworkListener*>* _listeners[PacketType :: LAST_TYPE];
	ENetAddress _address;
	ENetHost* _host;
	ENetEvent _event;
	ENetPeer* _peer;

public:
	~Network();
	static Network* GetInstance();
	static bool isInitialized;

	void InitializeClient(const char* ipAdress);
	void InitializeServer();

	bool IsServer();
	bool IsConnected();

	void SendPacket(NetworkPacket packet, const bool reliable = false);
	void AddListener(PacketType packetType, const INetworkListener* listener);
	void Update();
	void DistributePacket(NetworkPacket packet);
};

#endif
