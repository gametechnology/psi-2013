#include "Player.h"
#include "Messages.h"

Player::Player(Composite* parent) : Entity(parent)
{

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
