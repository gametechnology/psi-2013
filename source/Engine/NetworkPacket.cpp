#include <Engine\NetworkPacket.h>
#include <iostream>


NetworkPacket::NetworkPacket(const PacketType type) : _type(type)
{
}

NetworkPacket::NetworkPacket(ENetPacket* packet)
{
	clear();
	append(packet->data, packet->dataLength);

	int type;
	*this >> type;
	_type = (PacketType)type;
}

NetworkPacket::~NetworkPacket()
{
}

const size_t NetworkPacket::GetSize()
{
	return getDataSize() + sizeof(_type);
}
	
const void* NetworkPacket::GetBytes()
{
	sf::Packet tempPacket = _packet;
	clear();
	*this << _type;
	append(tempPacket.getData(), tempPacket.getDataSize());

	return getData();
}

PacketType NetworkPacket::GetType()
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
