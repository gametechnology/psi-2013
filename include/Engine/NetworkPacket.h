#ifndef NETWORKPACKET
#define NETWORKPACKET

#include "Network.h"
#include "SFML\Network.hpp"
#include "Irrlicht\irrlicht.h"

class NetworkPacket : public sf::Packet
{
public:
	NetworkPacket(const PacketType type);
	NetworkPacket(ENetPacket* packet);
	~NetworkPacket();
	const void* GetBytes();
	const size_t GetSize();
	bool reliable;
	PacketType GetType();

	friend sf::Packet& operator <<(sf::Packet& out, const irr::core::vector3df &in);
	friend sf::Packet& operator >>(sf::Packet& in, irr::core::vector3df& out);
	friend sf::Packet& operator <<(sf::Packet& out, const irr::core::vector2df& in);
	friend sf::Packet& operator >>(sf::Packet& in, irr::core::vector2df& out);

	friend sf::Packet& operator <<(sf::Packet& out, const irr::core::array<irr::core::vector3df>& in);
	friend sf::Packet& operator >>(sf::Packet& in, irr::core::array<irr::core::vector3df>& out);

private:
	PacketType _type;
	sf::Packet _originalPacket;
	sf::Packet _packet;
};



#endif