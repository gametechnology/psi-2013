#ifndef NETWORKPACKET
#define NETWORKPACKET

#include "Network.h"
#include "SFML\Network.hpp"
#include "Irrlicht\irrlicht.h"

class NetworkPacket : public sf::Packet
{
public:
	NetworkPacket(const PacketType type);
	NetworkPacket(ENetPacket* packet, ENetPeer peer);
	NetworkPacket(ENetPacket* packet);
	~NetworkPacket();
	const void* GetBytes();
	const size_t GetSize();
	const ENetPeer GetSender();
	bool reliable;
	PacketType GetType();

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
	ENetPeer _peer;
	PacketType _type;
	sf::Packet _originalPacket;
	sf::Packet _packet;
	
};



#endif