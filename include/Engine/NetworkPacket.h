#ifndef NETWORKPACKET
#define NETWORKPACKET

#include "Network.h"
#include "SFML\Network.hpp"
#include "Irrlicht\irrlicht.h"

class NetworkPacket : public sf::Packet
{
public:
	NetworkPacket(const PacketType type);
	NetworkPacket(ENetPacket* packet, enet_uint32);
	~NetworkPacket();
	const void* GetBytes();
	const size_t GetSize();
	bool reliable;
	PacketType GetType();

	enet_uint32 ipadress;

	friend sf::Packet& operator <<(sf::Packet& out, const irr::core::vector3df &in);
	friend sf::Packet& operator >>(sf::Packet& in, irr::core::vector3df& out);

	friend sf::Packet& operator <<(sf::Packet& out, const irr::core::vector2df& in);
	friend sf::Packet& operator >>(sf::Packet& in, irr::core::vector2df& out);

	friend sf::Packet& operator <<(sf::Packet& out, const std::vector<irr::core::vector3df>& in);
	friend sf::Packet& operator >>(sf::Packet& in, std::vector<irr::core::vector3df>& out);

	friend sf::Packet& operator <<(sf::Packet& out, const std::vector<irr::core::vector2df>& in);
	friend sf::Packet& operator >>(sf::Packet& in, std::vector<irr::core::vector2df>& out);

	friend sf::Packet& operator <<(sf::Packet& out, const std::vector<bool>& in);
	friend sf::Packet& operator >>(sf::Packet& in, std::vector<bool>& out);

	friend sf::Packet& operator <<(sf::Packet& out, const std::vector<int>& in);
	friend sf::Packet& operator >>(sf::Packet& in, std::vector<int>& out);

	friend sf::Packet& operator <<(sf::Packet& out, const std::vector<float>& in);
	friend sf::Packet& operator >>(sf::Packet& in, std::vector<float>& out);

private:
	PacketType _type;
	sf::Packet _originalPacket;
	sf::Packet _packet;
};



#endif