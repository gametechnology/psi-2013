#ifndef NETWORKPACKET
#define NETWORKPACKET

#include "Network.h"

class NetworkPacket
{
public:
	NetworkPacket(PacketType type);
	~NetworkPacket();
private:
	PacketType _type;
};

#endif