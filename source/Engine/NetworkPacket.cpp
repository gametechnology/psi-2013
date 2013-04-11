#include "Engine\NetworkPacket.h"
#include <iostream>


NetworkPacket::NetworkPacket(const PacketType type, const sf::Packet packet) : _type(type), _packet(packet)
{
}

NetworkPacket::NetworkPacket(ENetPacket* packet)
{
	_packet.append(packet->data, packet->dataLength);
	const void* data = _packet.getData();
	_typee = ntohl(*reinterpret_cast<const int*>(_packet.getData()) + _packet.getDataSize() - sizeof(PacketType)); 
	_type = (PacketType)_typee;

}

NetworkPacket::~NetworkPacket()
{
}

const size_t NetworkPacket::GetSize()
{
	return sizeof(_type) + _packet.getDataSize();
}

const void* NetworkPacket::GetBytes()
{
	return _packet.getData();	
}

sf::Packet NetworkPacket::GetPacket()
{
	return _packet;
}

PacketType NetworkPacket::GetPacketType()
{
	return _type;
}
