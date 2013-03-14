#include "stdafx.h"


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
		static int lastpackageids[];
		static int lastpackageid;
		static int packageidsend = 0;
		static void senderthread(void * var)
		{    
			sf::SocketUDP Socket;
			//TODO write recieve data code.
			int x;
			int y;
			int z;
			
			while(true){
				
				if (isServer ==  FALSE){
					sf::Packet packettosend;
					std::string header = "RegUpdt";
					packettosend << header << playernumber << packageidsend  << x << y  << z ;
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
				packageidsend++;
				Sleep(30);
			}
			Socket.Close();
			return;
		}
		static void  recieverthread(void * var)
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
						int packageid;
						float x;
						float y;
						float z;
						packettorecieve >> playernumber >> packageid >> x >> y >> z ;
						if((isServer == true && lastpackageids[playernumber -1] < packageid) || (isServer == false && lastpackageid < packageid))
						{
							//update code;
							if (isServer == true)
							{
								lastpackageids[playernumber -1] = packageid;
								for (list<int>::ConstIterator iterator = clientip.begin(); iterator != clientip.end(); ++iterator) {
									//TODO some check that we don't send to client we recieved from
									sf::Packet packettosend;
									std::string header = "RegUpdt";
									packettosend << header << playernumber << packageidsend << x << y  << z ;
									if (Socket.Send(packettosend, *iterator, 7000) != sf::Socket::Done)
									{
										// Error...
			
									}
								}
								packageidsend++;
							}
							else
							{
								lastpackageid = packageid;
							}
						}
					}
				}
			}
			Socket.Close();
			return;
		}
	public:
		Net();		
		Net(std::string);
		void StartGame();
};
		BOOLEAN Net:: isServer;
		std::string Net:: serverip;
		BOOLEAN Net:: isrunning;
		int Net:: playernumber;
		list<int> Net:: clientip;
		
		/*
		Use this function if you are the server
		*/
		Net::Net()
		{
			Net::isServer = TRUE;
			_beginthread(senderthread,0,NULL);
			_beginthread(recieverthread,0,NULL);
			//TODO write connect code;
		}
		/*
		Use this function if you are a client an pass the server of the as the parameter.
		*/
		Net::Net(std::string ipadres)
		{
			Net::serverip = ipadres;
			Net::isServer = FALSE;
			
			//TODO write connect code;

		}	
		void Net::StartGame(){
			// TODO write start game code;
		}

