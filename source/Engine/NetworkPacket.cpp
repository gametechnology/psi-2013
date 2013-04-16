#include "Engine\NetworkPacket.h"
#include <iostream>


NetworkPacket::NetworkPacket(const PacketType type, const sf::Packet packet) : _type(type), _packet(packet)
{
}

NetworkPacket::NetworkPacket(ENetPacket* packet)
{
	_packet.clear();
	_packet.append(packet->data, packet->dataLength);

	int type;
	_packet >> type;
	_type = (PacketType)type;
}

NetworkPacket::~NetworkPacket()
{
}

const size_t NetworkPacket::GetSize()
{
	return _packet.getDataSize() + sizeof(_type);
}
	
const void* NetworkPacket::GetBytes()
{
	sf::Packet tempPacket = _packet;
	_packet.clear();
	_packet << _type;
	_packet.append(tempPacket.getData(), tempPacket.getDataSize());

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

sf::Packet& operator >>(sf::Packet &out, const irr::core::vector3df &in)
{
	return out << in.X << in.Y << in.Z;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::vector3df& out)
{
	return in >> out.X >> out.Y >> out.Z;
}

sf::Packet& operator <<(sf::Packet& out, const irr::core::vector2df& in)
{
	return out << in.X << in.Y;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::vector2df& out)
{
	return in >> out.X >> out.Y;
}
