#include "stdafx.h"
#include "client.h"


		Client::Client(std::string ipadress,int playernumber,std::string name)
		{
			Ipadress = ipadress;
			Playernumber = playernumber;
			Name = name;
		}
		Client::Client(){};
				
		sf::Packet& operator <<(sf::Packet& Packet, const Client& C)
		{
			return Packet << C.Ipadress << C.Name << C.Playernumber;
		}
		sf::Packet& operator >>(sf::Packet& Packet, Client& C)
		{
			return Packet >> C.Ipadress >> C.Name >> C.Playernumber;
		}