#ifndef INETWORKLISTENER
#define INETWORKLISTENER

#include "Network.h"

// forward declare NetworkPacket
class NetworkPacket;

class INetworkListener
{
public:
	virtual void handleNetworkMessage(NetworkPacket packet) = 0;

	~INetworkListener()
	{
		Network::GetInstance()->RemoveListener(this);
	}
};

#endif