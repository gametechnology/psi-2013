#include "stdafx.h"
#include "net.h"


	BOOLEAN Net::isServer;
	std::string Net::serverip;
	BOOLEAN Net::isrunning;
	list<Client> Net::clientlist;
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

		
		
		/*
		Use this function if you are the server
		*/
		Net::Net()
		{
					isServer = TRUE;
					/*
					_beginthread(senderthread,0,NULL);
					_beginthread(recieverthread,0,NULL);*/
			//TODO write connect code;
		}
		/*
		Use this function if you are a client an pass the server of the as the parameter.
		*/
		Net::Net(std::string ipadres)
		{			

					serverip = ipadres;
					isServer = FALSE;
					/*
					_beginthread(senderthread,0,NULL);
					_beginthread(recieverthread,0,NULL);*/
			//TODO write connect code;

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
