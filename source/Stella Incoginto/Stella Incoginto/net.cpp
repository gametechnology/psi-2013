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
		case 0:
			if(!isServer)
			{
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
					
				} 
			}
		case 1:
			if(isServer)
			{
				//create and fill the initctos struct.
				sf::Packet lobbyPackage;
				std::string header = "lobbyupdate";
				lobbyPackage << header << static_cast<sf::Uint32>(clientlist.size());
				for (list<Client>::Iterator it = clientlist.begin(); it != clientlist.end(); ++it)
					lobbyPackage << *it;
				for (list<Client>::Iterator i = clientlist.begin(); i != clientlist.end(); i++)
				{
					
					if (Socket.Send(lobbyPackage,  i->Ipadress, 8008) != sf::Socket::Done)
					{
					
					}
				}
			}
			break;

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
			mypc.lastpackageid++;
			break;
		default:
			break;
		}
		
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
			if (header == "initctos")
			{
				std::string name;
				packettorecieve >> name;
				Client * sender = GetClientByIp(Sender.ToString());
				if(isServer)
				{
					if(sender != NULL)
						continue;
					clientlist.push_front(Client(Sender.ToString(),num_players_con + 1,name));
					num_players_con++;
				}
				
			}
			if (header == "initctos_conf")
			{
				if(!isServer)
				{
					stagegame = 1;
					sf::Uint32 size;
					packettorecieve >> size;
					for (sf::Uint32 i = 0; i < size; ++i)
					{
						Client item;
						packettorecieve >> item;
						Client * sender = GetClientByIp(Sender.ToString());
						if(sender == NULL)
							clientlist.push_back(item);
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
	return NULL;
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

Net::Net(std::string ipadres, std::string name)
{
	serverip = ipadres;
	isServer = FALSE;
	mypc.Name = name;
	int  a =1;
	_beginthread(senderthread, 0, &a);
	_beginthread(recieverthread, 0, &a);
} 

		
Net::Net(std::string name)
{
	isServer = TRUE;
	mypc.Name = name;
	clientlist.push_back(Client("",1,name));
	num_players_con++;
	int  a =1;
	_beginthread(senderthread, 0, &a);
	_beginthread(recieverthread, 0, &a);
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
