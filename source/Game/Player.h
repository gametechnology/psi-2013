#ifndef PLAYER
#define PLAYER

#include "Engine/Entity.h"
#include "Engine/NetworkPacket.h"
class Player : public Entity  {
public:
	wchar_t* Name;
	int Team;
	enet_uint32 Ipadres;

	Player();
	Player( wchar_t * name, enet_uint32 ipadres, int team);
	~Player();

	void handleMessage(unsigned int message, void* data = 0);

	/*
	* Gets the stationtype this player is currently using.
	* You can cast an unsigned int to an enumeration easely
	* by using code like this:
	* <EnumType> var = (<EnumType>) [The unsigned int];
	*/
	unsigned int getCurrentStation();

	/*
	* Sets the stationtype this player is currently using.
	* -
	* DO NOT use this function directly. The station code uses this function.
	* It will not break the code but it will give strange behaviour.
	*/
	void setStation(unsigned int station);

	/*
	* Reset the occupational variables of this Player instance.
	* The getCurrentStation function will return 999 if called straight
	* after this function.
	* -
	* DO NOT use this function directly. The station code uses this function.
	* It will not break the code but it will give strange behaviour.
	*/
	void resetStation();
private:
	unsigned int _station;
};

sf::Packet& operator >>(sf::Packet& in, Player * out);

sf::Packet& operator <<(sf::Packet& out, const Player * in);

#endif
