#include "net.h"
#include "WeaponCameraMover.h"		
matrix4 WeaponCameraMover::helmrotation;
		sf::Packet& operator <<(sf::Packet& Packet, const vector3df& C)
		{
			
			return Packet << C.X << C.Y << C.Z;
		}

		sf::Packet& operator >>(sf::Packet& Packet, vector3df& C)
		{
			
			return Packet >> C.X >> C.Y >> C.Z;
		}
		int Net::packageid;

		void Net::senderthread(void * var)
		{    
			sf::SocketUDP Socket;
			Camera * node = (Camera*)var;
			packageid = 0;
			while(true){
				sf::Packet packettosend;
				vector3df position = node->getCameraNode()->getPosition();
				vector3df rotation = node->getCameraNode()->getRotation();
				packageid++;
				packettosend << packageid << position << rotation;
				
				// Create the UDP socket
		
				if (Socket.Send(packettosend, "145.92.73.131", 7000) != sf::Socket::Done)
				{
					// Error...
			
				}
				Sleep(30);
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
						vector3df position;
						vector3df rotation;
						packettorecieve >> position >> rotation;
						nodeother->getCameraNode()->setPosition(position);
						//WeaponCameraMover::helmrotation = affector;
						nodeother->getCameraNode()->setRotation(rotation);
						
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
		