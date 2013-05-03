#include <Engine\NetworkPacket.h>
#include <iostream>


NetworkPacket::NetworkPacket(const PacketType type) : _type(type)
{
}

NetworkPacket::NetworkPacket(ENetPacket* packet, enet_uint32 ipadressrec)
{
	ipadress = ipadressrec;
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
	sf::Packet tempPacket = *this;
	clear();
	*this << _type;
	append(tempPacket.getData(), tempPacket.getDataSize());

	return getData();
}

PacketType NetworkPacket::GetType()
{
	return _type;
}

sf::Packet& operator <<(sf::Packet &out, const irr::core::vector3df &in)
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

sf::Packet& operator <<(sf::Packet& out, const irr::core::array<irr::core::vector3df>& in)
{
	out << in.size();
	for(unsigned int i = 0; i < in.size(); i++)
	{
		out << in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::array<irr::core::vector3df>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		irr::core::vector3df vector3;
		in >> vector3;
		out.push_back(vector3);
	}
	return in;
}

sf::Packet& operator <<(sf::Packet& out, const irr::core::array<irr::core::vector2df>& in)
{
	out << in.size();
	for(unsigned i = 0; i < in.size(); i++)
	{
		out << in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::array<irr::core::vector2df>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		irr::core::vector2df vector2;
		in >> vector2;
		out.push_back(vector2);
	}
	return in;
}

sf::Packet& operator <<(sf::Packet& out, const irr::core::array<bool>& in)
{
	out << in.size();
	for(unsigned i = 0; i < in.size(); i++)
	{
		out << in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::array<bool>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		bool tempBool;
		in >> tempBool;
		out.push_back(tempBool);
	}
	return in;
}

sf::Packet& operator <<(sf::Packet& out, const irr::core::array<int>& in)
{
	out << in.size();
	for(unsigned int i = 0; i < in.size(); i++)
	{
		out << in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::array<int>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		int j;
		in >> j;
		out.push_back(j);
	}
	return in;
}

sf::Packet& operator <<(sf::Packet& out, const irr::core::array<float>& in)
{
	out << in.size();
	for(unsigned int i = 0; i < in.size(); i++)
	{
		out << in[i];
	}
	return out;
}

sf::Packet& operator >>(sf::Packet& in, irr::core::array<float>& out)
{
	int size;
	in >> size;
	for(int i = 0; i < size; i++)
	{
		float j;
		in >> j;
		out.push_back(j);
	}
	return in;
}
