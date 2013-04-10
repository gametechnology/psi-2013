#ifndef NETWORK
#define NETWORK

class Network
{
private:
	Network();

	static Network* instance;
public:
	~Network();
	static Network* GetInstance();
	static bool isInitialized;

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
