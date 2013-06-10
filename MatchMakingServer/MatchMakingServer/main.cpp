#include "SFML\Network.hpp";
#include <list>;
#include <iostream>;
struct host{
	sf::IpAddress ip;
	wchar_t*  name;
};
std::list<host> iplist;
int main()
{
	
	while(true){

		sf::UdpSocket Socket;
		// Bind it (listen) to the port 4567
		if (!Socket.bind(4567))
		{
			// Error...
		}
		sf::Packet recievepacket;
		sf::IpAddress Sender;
		unsigned short Port;
		std::cout << "waiting for packet...\n";
		if (Socket.receive(recievepacket, Sender, Port) != sf::Socket::Done)
		{
			// Error...
		}
		else
		{
			bool isserver;
			
			recievepacket >> isserver;
			if (isserver)
			{
				std::cout << "Host Connected\n";
				bool alreadyin = false;
				std::list<host>::iterator iterator;
				for (iterator = iplist.begin(); iterator != iplist.end(); ++iterator) {		
					if(Sender.toInteger() ==  (*iterator).ip.toInteger()){
						alreadyin = true;
						break;
					}
						
				}
				if(!alreadyin){
					wchar_t*  name;
					recievepacket >> name;
					host hoster;
					hoster.ip = Sender;
					hoster.name = name;
					iplist.push_back(hoster);
				}
			}
			else
			{
				std::cout << "Client request\n";
				// Create bytes to send
				char Buffer[] = "Hi guys !";
				sf::Packet sendpacket;
				sendpacket << iplist.size();
				std::list<host>::iterator iterator;
				for (iterator = iplist.begin(); iterator != iplist.end(); ++iterator) {		
					sendpacket << (*iterator).ip.toString();
					sendpacket << (*iterator).name;
				}
				// Send data to "192.168.0.2" on port 4567
				if (Socket.send(sendpacket, Sender, 4567) != sf::Socket::Done)
				{
					// Error...
				}
			}
		}

		
	}
	

}