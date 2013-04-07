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
sf::Packet& operator <<(sf::Packet& Packet, const Bullet& C)
{

	return Packet << C.position << C.orientation << C.visible;
}

sf::Packet& operator >>(sf::Packet& Packet, Bullet& C)
{

	return Packet >> C.position >> C.orientation >> C.visible;
}
int Net::packageid;
int Net::packageidrecieve;
std::string Net::ipAddress;

void Net::senderthread(void * var)
{    
	packageid = 0;
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

		if (Socket.Send(packettosend, Net::ipAddress, 30000) != sf::Socket::Done)
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
	packageid = 0;
	WeaponCameraMover * nodeother = (WeaponCameraMover*)var;
	Camera* camera = nodeother->camera;
	sf::SocketUDP Socket;

	if (!Socket.Bind(30000))
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
			if(recievedpackageid > packageidrecieve){
				packageidrecieve = recievedpackageid;
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

void Net::senderthreadWeapon(void * var)
{    
	sf::SocketUDP Socket;
	Bullet * node = (Bullet*)var;

	while(true){
		sf::Packet packettosend;

		packageid++;
		packettosend << packageid << 10;

		for (int i = 0; i < 10; i++)
		{
			packettosend << node[i];
		}

		// Create the UDP socket

		if (Socket.Send(packettosend, Net::ipAddress, 30000) != sf::Socket::Done)
		{
			// Error...

		}
		Sleep(30);
	}
	Socket.Close();
	return;
}
void  Net::revieverthreadWeapon(void * var)
{
	Bullet * nodeother = (Bullet*)var;
	sf::SocketUDP Socket;
	if (!Socket.Bind(30000))
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
			if(recievedpackageid > packageidrecieve){
				packageidrecieve = recievedpackageid;
				int length;
				packettorecieve >> length;
				for (int i = 0; i < length; i++)
				{
					packettorecieve >> nodeother[i];
				}
			}
		}

	}
	Socket.Close();
	return;
}

Net::Net(bool IsWeapon, void * sendervar, void * recievervar)
{
	std::cout << "ip address of other pc" << std::endl;
	std::cin >> Net::ipAddress;

	if(IsWeapon)
	{
		_beginthread(senderthreadWeapon,0, sendervar);

		_beginthread(revieverthread,0, recievervar);
	}
	else
	{
		_beginthread(senderthread,0, sendervar);

		_beginthread(revieverthreadWeapon,0, recievervar);
	}
}	
Net::Net(){

}
