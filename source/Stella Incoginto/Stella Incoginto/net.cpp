#include "stdafx.h"

#include <irrlicht.h>
#include <process.h>
#include <sstream>
#include <SFML/Network.hpp>


using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;


#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif
	
class Net{
	private:
		static void senderthread(void * var)
		{    
			sf::SocketUDP Socket;
			IAnimatedMeshSceneNode * node = (IAnimatedMeshSceneNode*)var;
			
			while(true){
				sf::Packet packettosend;
				vector3df position = node->getPosition();

				packettosend << position.X << position.Y  << position.Z ;
				// Create the UDP socket
		
				if (Socket.Send(packettosend, "192.168.2.8", 7000) != sf::Socket::Done)
				{
					// Error...
			
				}
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
					float x;
					float y;
					float z;
					packettorecieve >> x >> y >> z ;
		
					nodeother->setPosition(vector3df(x,y,z));
			
			
				}
			}
			Socket.Close();
			return;
		}
	public:
		Net(void *, void *);			
};
		Net::Net(void * player1, void * player2)
		{
			//begin threads	
			_beginthread(senderthread,0, player1);
			_beginthread(revieverthread,0, player2);
		}	


