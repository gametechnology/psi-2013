#ifndef INETWORKLISTENER
#define INETWORKLISTENER

#include "Network.h"

// forward declare NetworkPacket
class NetworkPacket;

class INetworkListener
{
public:
	virtual void HandleNetworkMessage(NetworkPacket packet) = 0;

	~INetworkListener()
	{
		Network::GetInstance()->RemoveListener(this);
	}
};

#endif