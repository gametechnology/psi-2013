#include "net.h"
#include "WeaponCameraMover.h"		

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
			packageid = 0;
			sf::SocketUDP Socket;
			Camera * node = (Camera*)var;
			
			while(true){
				sf::Packet packettosend;
				vector3df position = node->getCameraNode()->getPosition();

				packettosend << packageid << node->getCameraNode()->getPosition() << node->getCameraNode()->getRotation();
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
			packageid = 0;
			WeaponCameraMover * nodeother = (WeaponCameraMover*)var;
			Camera* camera = nodeother->camera;
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
						packageid = recievedpackageid;
						vector3df position;
						vector3df rotation;
						packettorecieve >> position >> rotation;
						camera->getCameraNode()->setPosition(position);
						
						nodeother->helmrotation = rotation;
						
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
		