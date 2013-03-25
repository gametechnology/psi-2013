#include "net.h"
		
		sf::Packet& operator <<(sf::Packet& Packet, const matrix4& C)
		{
			for(int i =0; i < 16; i++){
				Packet << C[i];
			}
			return Packet;
		}

		sf::Packet& operator >>(sf::Packet& Packet, matrix4& C)
		{
			for(int i =0; i < 16; i++){
				Packet >> C[i];
			}
			return Packet;
		}
		int Net::packageid;

		void Net::senderthread(void * var)
		{    
			sf::SocketUDP Socket;
			Camera * node = (Camera*)var;
			
			while(true){
				sf::Packet packettosend;
				vector3df position = node->getCameraNode()->getPosition();

				packettosend << packageid << position.X << position.Y  << position.Z << node->getCameraNode()->getViewMatrixAffector();
				// Create the UDP socket
		
				if (Socket.Send(packettosend, "192.168.2.8", 7000) != sf::Socket::Done)
				{
					// Error...
			
				}
			}
			Socket.Close();
			return;
		}
		void  Net::revieverthread(void * var)
		{
			Camera * nodeother = (Camera*)var;
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
					
					int recievedpackageid;
					packettorecieve >> recievedpackageid ;
					if(recievedpackageid > packageid){
						float x;
						float y;
						float z;
						matrix4 affector;
						packettorecieve >> x >> y >> z >> affector;
						nodeother->getCameraNode()->setPosition(vector3df(x,y,z));
						nodeother->getCameraNode()->setViewMatrixAffector(affector);
					}
					
			
			
				}
			}
			Socket.Close();
			return;
		}
		
		Net::Net(bool IsWeapon, void * cam)
		{
			//begin threads	
			if(!IsWeapon){
			_beginthread(senderthread,0, cam);
			}
			else{
			_beginthread(revieverthread,0, cam);
			}
		}	
		Net::Net(){
		
		}
		