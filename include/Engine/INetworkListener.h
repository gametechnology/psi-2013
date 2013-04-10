#ifndef INETWORKLISTENER
#define INETWORKLISTENER

#include "Engine/NetworkPacket.h"

class INetworkListener
{
public:
	virtual HandleNetworkMessage(NetworkPacket packet) = 0;
};

#endif