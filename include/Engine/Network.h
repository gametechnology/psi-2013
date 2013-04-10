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

#endif

