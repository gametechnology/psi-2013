#ifndef NETWORK
#define NETWORK

#include "Engine\INetworkListener.h"
#include <list>

// forward declare NetworkPacket to prevent circular dependancy
class NetworkPacket;

class Network
{
private:
	Network();

	static Network* instance;

	std::list<const INetworkListener*> _listeners;
public:
	~Network();
	static Network* GetInstance();
	static bool isInitialized;

	void InitializeClient();
	void InitializeServer();

	void SendPacket(const NetworkPacket packet, const bool reliable = false);
	void AddListener(const INetworkListener* listener);

	bool isServer;
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
