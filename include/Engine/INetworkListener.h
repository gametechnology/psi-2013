#ifndef INETWORKLISTENER
#define INETWORKLISTENER

// forward declare NetworkPacket
class NetworkPacket;

class INetworkListener
{
public:
	virtual void HandleNetworkMessage(NetworkPacket packet) = 0;
};

#endif