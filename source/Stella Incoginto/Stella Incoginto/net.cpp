#include "stdafx.h"

#include "NetSup.h"
#include <process.h>
#include <sstream>



using namespace irr;

using namespace core;
using namespace scene;
using namespace video;



#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Net{
private:
	static BOOLEAN isServer;
	static std::string serverip;
	static BOOLEAN isrunning;
	static int playernumber;
	static list<int> clientip;

	static void senderthread(void * var)
	{    
		sf::SocketUDP Socket;
		//TODO write recieve data code.
		int x;
		int y;
		int z;

		while(true){
			int packageid = 0;
			if (isServer ==  FALSE){
				sf::Packet packettosend;
				std::string header = "RegUpdt";
				packettosend << header << playernumber << packageid << x << y  << z ;
				if (Socket.Send(packettosend, serverip, 7000) != sf::Socket::Done)
				{
					// Error...

				}
			}
			else
			{

				for (list<int>::ConstIterator iterator = clientip.begin(); iterator != clientip.end(); ++iterator) {
					sf::Packet packettosend;
					std::string header = "RegUpdt";
					packettosend << header << playernumber << x << y  << z ;
					if (Socket.Send(packettosend, *iterator, 7000) != sf::Socket::Done)
					{
						// Error...

					}
				}
			}
			Sleep(30);
		}
		Socket.Close();
		return;
	}
	static void  revieverthread(void * var)
	{
		IAnimatedMeshSceneNode * nodeother = (IAnimatedMeshSceneNode*)var;
		sf::SocketUDP Socket;
		if (!Socket.Bind(7000))
			return;

		while (true)
		{
			sf::Packet packettorecieve;
			sf::IPAddress Sender;
			unsigned short Port;
			if (Socket.Receive(packettorecieve, Sender, Port) != sf::Socket::Done)
			{
				// Error...

			}
			else{
				std::string header;
				packettorecieve >> header;
				if (header == "RegUpdt"){

					int playernumber;
					float x;
					float y;
					float z;
					packettorecieve >> playernumber >> x >> y >> z ;
					//TODO update datar recieved;
					if (isServer == true)
					{
						for (list<int>::ConstIterator iterator = clientip.begin(); iterator != clientip.end(); ++iterator) {
							//TODO some check that we don't send to client we recieved from
							sf::Packet packettosend;
							std::string header = "RegUpdt";
							packettosend << header << playernumber << x << y  << z ;
							if (Socket.Send(packettosend, *iterator, 7000) != sf::Socket::Done)
							{
								// Error...

							}
						}
					}
				}
			}
		}
		Socket.Close();
		return;
	}
	//TODO write check package recieved code.
public:
	Net();		
	Net(std::string);
	void StartGame()
	{
		if(isServer)
		{
			// Create an UDP socket.
			sf::SocketUDP Socket;
			// Copy the list with client IPs so we can remove clients that have responded.
			list<int> copyclientip = clientip;

			while(true)
			{
				// Loop through the clients.
				for (list<int>::Iterator i = copyclientip.begin(); i != copyclientip.end(); i++)
				{
					// Send a packet with header StartGame and a begin position to the client.
					sf::Packet packettosend;
					std::string header = "StartGame";
					packettosend << header << playernumber << 0 << 0 << 0 ;
					if (Socket.Send(packettosend, *i, 7000) != sf::Socket::Done) 
					{ 
						// Error.
					}

					Sleep(1000);

					sf::Packet packettorecieve;
					sf::IPAddress Sender;
					unsigned short Port;
					if (Socket.Receive(packettorecieve, Sender, Port) != sf::Socket::Done)
					{
						// Error.
					}
					else
					{
						std::string header;
						packettorecieve >> header;
						if (header == "StartGameAck")
						{
							for (list<int>::Iterator i = copyclientip.begin(); i != copyclientip.end(); i++)
							{
								if(Sender == *i)
								{
									// Remove the client ip that responded from the list.
									copyclientip.erase(i);
									break;
								}
							}
						}
					}
				}
				// Stop sending packets when every client has responded.
				if(copyclientip.size() == 0)
				{
					break;
				}
			}
		}
	}
};
/*
Use this function if you are the client
*/
Net::Net(std::string ipadres)
	{
		serverip = ipadres;
		isServer = FALSE;
		//create and open the socket~
		sf::SocketUDP Socket;
		if (!Socket.Bind(8008))
			return;

		//create and fill the initctos struct.
		sf::Packet initPackage;
		initctos initctos;
		initctos.header = "initctos";
		initctos.name = "temp";
		initctos.id = 0;
		//put the struct into a package and send
		initPackage << initctos.header << initctos.name << initctos.id;
		if (Socket.Send(initPackage, serverip, 8008) != sf::Socket::Done)
		{
			printf("Client failed to send package \n should prolly try again");
		} 
		else
		{
			printf("Client sent init package, now wait for confirmation");
			bool received = false;
			sf::Packet initctos_confPackage;
			sf::IPAddress Sender;
			unsigned short Port;
			//while package isn't received, or failed to receive, keep trying to receive.
			//TODO: needs a timer for necessary resend and timeout.
			while(!received){
				if (Socket.Receive(initctos_confPackage, Sender, Port) != sf::Socket::Done && Sender == serverip)
				{
					printf("Client: Init confirmation Package failed to receive");
				} else{
					received = true;
				}
			}
			printf("Client: Confirmation received");
		} 

		
Net::Net()
{
	isServer = TRUE;
	sf::SocketUDP Socket;
	sf::IPAddress Sender;
	unsigned short Port;
	if (!Socket.Bind(Port))
		return;
	while(true){
		sf::Packet initPackage;
		initctos init;
		if (Socket.Receive(initctos_confPackage, Sender, Port) != sf::Socket::Done)
		{
			printf("Server: package failed to receive");
		}
		initPackage >> init.header >> init.name >>init.id;
		if (init.header == "initctos"){
			//unpack the package, and put it in an struct
			bool clientAdded = false;
			packettorecieve >> init.id >> init.name;
			//check the current netPlayers arrays list to see if the player trying to connect is already added.
			//if not, the player gets added to the clients list.
			for(int i = 0; i < 8; i++){
				if(clients[i].name != NULL){
					clients[num_players_con].adress =  &Sender;
					clients[num_players_con].name = &init.name;
				}
					clientAdded = true;
			} 
			if(clientAdded){
				sf::Packet confirmation_package;
				initctos_conf confirmation;
				confirmation.header = "initctos_conf";
				confirmation.name = init.name;
				confirmation.id = init.id;
				confirmation_package << confirmation.header << confirmation.name << confirmation.id;
				if (Socket.Send(confirmation_package, Sender, 7000) != sf::Socket::Done)
				{
					printf("Server: Confirmation Package failed to send");
				}
				//create and send a confermation package to the client
				sf::Packet confirmation_package;
				initctos_conf confirmation;
				confirmation.header = "initctos_conf";
				confirmation.name = init.name;
				confirmation.id = init.id;
				confirmation_package << confirmation.header << confirmation.name << confirmation.id;
				if (Socket.Send(confirmation_package, Sender, 8008) != sf::Socket::Done)
				{
					printf("Server: Confirmation Package failed to send");
				}
			}
		
		}
		else {
			printf("Server: Package received is not an initctos package");
		}
	}//end of while loop
}	

