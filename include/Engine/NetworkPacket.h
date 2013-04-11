#ifndef NETWORKPACKET
#define NETWORKPACKET

#include "Network.h"
#include "SFML\Network.hpp"

class NetworkPacket
{
public:
	NetworkPacket(const PacketType type, const sf::Packet packet);
	NetworkPacket(ENetPacket* packet);
	~NetworkPacket();
	const void* GetBytes();
	const size_t GetSize();
	sf::Packet GetPacket();
private:
	PacketType _type;
	sf::Packet _originalPacket;
	sf::Packet _packet;
};

#endif