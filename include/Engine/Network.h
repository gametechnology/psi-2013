#ifndef NETWORK
#define NETWORK

// forward declare NetworkPacket to prevent circular dependancy
class NetworkPacket;

class Network
{
private:
	Network();

	static Network* instance;
public:
	~Network();
	static Network* GetInstance();
	static bool isInitialized;

	void InitializeClient();
	void InitializeServer();

	void SendPacket(NetworkPacket packet, bool reliable = false);

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
