#include "SFML\Network.hpp";
#include <list>;
#include <iostream>;
struct host{
	sf::IpAddress ip;
	wchar_t*  name;
	time_t timein;
};
std::list<host> iplist;
int main()
{
	
	while(true){

		sf::UdpSocket Socket;
		// Bind it (listen) to the port 4567
		if (!Socket.bind(4444))
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
						(*iterator).timein = time(0);
						break;
					}
						
				}
				if(!alreadyin){
					
				
					
					host hoster;
					wchar_t*name = new wchar_t[500];
			
					hoster.name = new wchar_t[500];
					
					recievepacket >> name;
					wcsncpy(hoster.name, name, wcslen(name));
					hoster.name[wcslen(name)] = 0;
					hoster.timein = time(0);
					hoster.ip = Sender;
					iplist.push_back(hoster);
					delete name;
				}
			}
			else
			{
				std::cout << "Client request\n";
				// Create bytes to send
				char Buffer[] = "Hi guys !";
				sf::Packet sendpacket;
				
				
				std::list<host>::iterator i = iplist.begin();
				while (i != iplist.end())
				{
					
					if ((time(0) - (*i).timein)  > 2000 )
					{
						iplist.erase(i++);  // alternatively, i = items.erase(i);
					}
					else
					{
						++i;
					}
				}
				sendpacket << static_cast<int>(iplist.size());
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