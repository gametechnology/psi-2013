#include "Player.h"
#include "Messages.h"

Player::Player() : Entity()
{
	Name = new wchar_t[500];
	_station = 999;
}
// TODO Check merge
Player::Player( wchar_t *namec, enet_uint32 ipadressc,int teamc ) : Entity()
{
	wcsncpy(Name, namec, wcslen(namec));
	Name[wcslen(namec)] = 0;
	Ipadres = ipadressc;
	Team = teamc;
}


void Player::handleMessage(unsigned int message, void* data) {
	delete data;
}

unsigned int Player::getCurrentStation()
{
	return _station;
}

void Player::setStation(unsigned int station)
{
	_station = station;
}

void Player::resetStation()
{
	_station = 999;
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
