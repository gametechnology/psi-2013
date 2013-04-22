#include "Player.h"
#include "Messages.h"


Player::Player(Composite* parent) : Entity(parent)
{
	Name = new wchar_t[500];
}

Player::Player(Composite* parent, wchar_t namec, enet_uint32 ipadressc,int teamc ) : Entity(parent)
{
	Name = new wchar_t[500];
	*Name = namec;
	Ipadres = ipadressc;
	Team = teamc;
}


void Player::handleMessage(unsigned int message, void* data) {
	//switch(message) {
		/* Do something */
		//default:
			//break;
	//}
	delete data;
}

Player::~Player()
{
	Entity::~Entity();
}
sf::Packet& operator >>(sf::Packet& in, Player * out)
{
	return in >> out->Name >> out->Team >> out->Ipadres;
}

sf::Packet& operator <<(sf::Packet& out, const Player * in)
{
	return out << in->Name << in->Team << in->Ipadres;
}
