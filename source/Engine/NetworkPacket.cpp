#include "Engine\NetworkPacket.h"

NetworkPacket::NetworkPacket(const PacketType type, const sf::Packet packet) : _type(type), _packet(packet)
{
}

NetworkPacket::~NetworkPacket()
{
}