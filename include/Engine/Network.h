#ifndef NETWORK
#define NETWORK

#include "Engine\INetworkListener.h"
#include <enet\enet.h>
#include <list>

// forward declare NetworkPacket to prevent circular dependancy
class NetworkPacket;

class Network
{
private:
	const int _port;

	Network();
	
	bool _isServer;
	bool _isConnected;
	static Network* instance;
	std::list<const INetworkListener*> _listeners;
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

	void SendPacket(const NetworkPacket packet, const bool reliable = false);
	void AddListener(const INetworkListener* listener);
};

enum PacketType
{
	CLIENT_JOIN = 0,
	CLIENT_QUIT,
	CLIENT_JOIN_TEAM,
	SERVER_WELCOMES,
	SERVER_REJECTS
};

#endif
