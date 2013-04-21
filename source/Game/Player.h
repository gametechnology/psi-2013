#ifndef PLAYER
#define PLAYER

#include "Engine/Entity.h"
#include "Engine/NetworkPacket.h"
class Player : public Entity  {
public:
	Player();
	~Player();
	wchar_t* Name;
	int Team;
	enet_uint32 Ipadres;
	void handleMessage(unsigned int message, void* data = 0);	
};
sf::Packet& operator >>(sf::Packet& in, Player * out);

sf::Packet& operator <<(sf::Packet& out, const Player * in);

#endif
