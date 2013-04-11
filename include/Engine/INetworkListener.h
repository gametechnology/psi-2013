#ifndef INETWORKLISTENER
#define INETWORKLISTENER

// forward declare NetworkPacket
class NetworkPacket;

class INetworkListener
{
public:
	virtual void HandleNetworkMessage(NetworkPacket packet) = 0;

	~INetworkListener()
	{
		//TODO: add remove this from the network::instance
	}
};

#endif