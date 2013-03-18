#ifndef Client_H
#define Client_H
#include "stdafx.h"

using namespace irr;

using namespace core;

class Client{	
	public:
		std::string Ipadress;
		int lastpackageid;
		list<int> lastimportantsendpackages;
		list<int> lastimportantrecievedpackages;
		int Playernumber;
		std::string Name;
		Client(std::string ipadress, int playernumber ,std::string name);
		friend sf::Packet& operator <<(sf::Packet& Packet, const Client& C);
		friend sf::Packet& operator >>(sf::Packet& Packet, Client& C);
		Client();
};
#endif