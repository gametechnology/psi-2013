#include "stdafx.h"
#include "net.h"
#include "NetSup.h"
#include "netSupPos.h"

BOOLEAN Net::isServer;
std::string Net::serverip;
BOOLEAN Net::isrunning;
list<Client> Net::clientlist;
list<Client> Net::copyclientlist;
int num_players_con = 0;
Client Net::mypc;
int Net::lastpackageidrecieved;

// 0 = connecting, 1 = inlobby, 2 = loading 3 = ingame
int Net::stagegame;

void Net::senderthread(void * var)
{    
	sf::SocketUDP Socket;
	//TODO write recieve data code.
	int x;
	int y;
	int z;

	while(true){
		switch(stagegame){
		case 2:
			if(isServer)
			{
				if(copyclientlist.size() == 0)
				{
					copyclientlist = clientlist;
				}
				// Loop through the clients.
				for (list<Client>::Iterator i = copyclientlist.begin(); i != copyclientlist.end(); i++)
				{
					// Send a packet with header StartGame and a begin position to the client.
					sf::Packet packettosend;
					std::string header = "StartGame";
					packettosend << header << 0 << 0 << 0 ;
					if (Socket.Send(packettosend, i->Ipadress, 7000) != sf::Socket::Done) 
					{ 
						// Error.
					}
				}
			}
			break;
		case 3:
			if (isServer ==  FALSE){
				sf::Packet packettosend;
				std::string header = "RegUpdt";
				packettosend << header << mypc.Playernumber << mypc.lastpackageid  << x << y  << z ;
				if (Socket.Send(packettosend, serverip, 7000) != sf::Socket::Done)
				{
					// Error...

				}
			}
			else
			{

				for (list<Client>::ConstIterator iterator = clientlist.begin(); iterator != clientlist.end(); ++iterator) {
					sf::Packet packettosend;
					std::string header = "RegUpdt";
					packettosend << header << mypc.Playernumber << x << y  << z ;
					if (Socket.Send(packettosend, iterator->Ipadress, 7000) != sf::Socket::Done)
					{
						// Error...

					}
				}
			}
			break;
		default:
			break;
		}
		mypc.lastpackageid++;
		Sleep(30);
	}
	Socket.Close();
	return;
}
void  Net::recieverthread(void * var)
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
				Client * sender = GetClientByIp(Sender.ToString());
				int playernumber;
				int packageid;
				float x;
				float y;
				float z;
				packettorecieve >> playernumber >> packageid >> x >> y >> z ;

				if((isServer == true && sender->lastpackageid < packageid) || (isServer == false && lastpackageidrecieved < packageid))
				{
					//update code;
							if(isServer == false) {
								UpdateGame(Socket, serverip, packageid);
							}
							lastpackageidrecieved = packageid;

					if (isServer == true)
					{
						sender->lastpackageid = packageid;
						for (list<Client>::ConstIterator iterator = clientlist.begin(); iterator != clientlist.end(); ++iterator) {
							//TODO some check that we don't send to client we recieved from
							if(iterator->Ipadress == Sender.ToString())
								continue;
							sf::Packet packettosend;
							std::string header = "RegUpdt";
							packettosend << header << playernumber << mypc.lastpackageid << x << y  << z ;
							if (Socket.Send(packettosend, iterator->Ipadress, 7000) != sf::Socket::Done)
							{
								// Error...

							}
						}
						mypc.lastpackageid++;
					}
					else
					{
						mypc.lastpackageid = packageid;
					}
				}
			}
		}
	}
	Socket.Close();
	return;
}

Client * Net::GetClientByIp(std::string ipadress)
{
	for (list<Client>::ConstIterator iterator = clientlist.begin(); iterator != clientlist.end(); ++iterator) {
		if(iterator->Ipadress == ipadress)
			return (Client*)&iterator;
	}
}

void Net::StartGame()
{
	if(isServer)
	{
		// Create an UDP socket.
		sf::SocketUDP Socket;
		// Copy the list with client IPs so we can remove clients that have responded.
		list<Client> copyclient = clientlist;

		while(true)
		{
			// Loop through the clients.
			for (list<Client>::Iterator i = copyclient.begin(); i != copyclient.end(); i++)
			{
				// Send a packet with header StartGame and a begin position to the client.
				sf::Packet packettosend;
				std::string header = "StartGame";
				packettosend << header << 0 << 0 << 0 ;
				if (Socket.Send(packettosend, i->Ipadress, 7000) != sf::Socket::Done) 
				{ 
					// Error.
				}



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
						for (list<Client>::Iterator i = copyclient.begin(); i != copyclient.end(); i++)
						{
							if(Sender == i->Ipadress)
							{
								// Remove the client ip that responded from the list.
								copyclient.erase(i);
								break;
							}
						}
					}
				}
			}
			// Stop sending packets when every client has responded.
			if(copyclient.size() == 0)
			{
				break;
			}
			Sleep(50);
		}
	}
}
/*
Use this function if you are the client
*/
void Net::InitiateNetC(void * ipadres){
	_beginthread(senderthread, 0, NULL);
	char * cip = ipadres;
	serverip = cip;
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
}

void Net::InitiateNetS(){
	isServer = TRUE;
	sf::SocketUDP Socket;
	sf::IPAddress Sender;
	unsigned short Port = 8008;
	if (!Socket.Bind(Port))
		return;
	while(true){
		sf::Packet initPackage;
		initctos init;
		if (Socket.Receive(initPackage, Sender, Port) != sf::Socket::Done)
		{
			printf("Server: package failed to receive");
		}
		initPackage >> init.header >> init.name >>init.id;
		if (init.header == "initctos"){
			//unpack the package, and put it in an struct
			bool clientAdded = false;
			bool clientAlreadyAdded = false;
			initPackage >> init.id >> init.name;
			//check the current netPlayers arrays list to see if the player trying to connect is already added.
			//if not, the player gets added to the clients list.

			for (list<Client>::Iterator i = clientlist.begin(); i != clientlist.end(); i++)
			{
				if(i->Name != init.name){
					clientlist.push_back(Client(Sender.ToString(), num_players_con, init.name));
					clientAdded = true;
				}
			} 
			if(clientAdded){
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

Net::Net(std::string ipadres)
{
	void *vp = static_cast<void*>(new std::string(ipadres));
	_beginthread(&Net::InitiateNetC, 0, &vp);
} 

		
Net::Net()
{
	int a = 1;
	_beginthread(&Net::InitiateNetS, 0, &a);
}	


void Net::UpdateGame(sf::SocketUDP Socket, std::string ipadres, int lastpackagerecieved)
{
	sf::Packet posupdate;
	initpos init;
	
	sf::IPAddress Sender;
	unsigned short Port;
	if (Socket.Receive(posupdate, Sender, Port) != sf::Socket::Done && Sender == serverip)
	{
		//printf("Client failed to recieve package");
	} else {
		posupdate >> init.header >> init.name >> init.id;
		if (init.header == "posupdate" && init.id > lastpackagerecieved) 
		{
			posupdate >> init.x >> init.y >> init.z;
		}
	}
}
