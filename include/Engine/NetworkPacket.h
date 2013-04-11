#ifndef NETWORKPACKET
#define NETWORKPACKET

#include "Network.h"
#include "SFML\Network.hpp"

class NetworkPacket
{
public:
	NetworkPacket(const PacketType type, const sf::Packet packet);
	~NetworkPacket();
private:
	PacketType _type;
	sf::Packet _packet;
};

#endif