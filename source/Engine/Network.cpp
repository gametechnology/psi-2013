#include "Engine\Network.h"
#include "Engine\NetworkPacket.h"
#include "Engine\INetworkListener.h"
#include <iostream>
#include "SFML\System.hpp"

bool Network::isInitialized = false;
Network* Network::instance = 0;

Network::Network() : _port(1345)
{
	_isServer = false;
	_isConnected = false;

	for (int i = 0; i < PacketType::LAST_TYPE; i++)
		_listeners[i] = new std::list<INetworkListener*>();

	if (enet_initialize() != 0)
		std::cout << "An error occurred while initializing ENet.\n";
}

Network::~Network()
{
	isInitialized = false;
}

Network* Network::GetInstance()
{
	if(!isInitialized)
	{
		instance = new Network();
		
		isInitialized = true;
	}

	return instance;
}

void Network::StartThreads()
{
	//_beginthread(PacketReciever,0, NULL);
	//_beginthread(PacketSender,0, NULL);
	
	sf::Thread thread1(&Network::PacketSender, this);
	thread1.launch();

	sf::Thread thread2(&Network::PacketReciever, this);
	//thread2.launch();
}

void Network::StopThreads()
{
	//_endthread();
}

void Network::InitializeClient(const char* ipAdress)
{
	std::cout << "Initializing client at port " << _port << ".\n";

	_host = enet_host_create (NULL /* create a client host */,
            1 /* only allow 1 outgoing connection */,
            2 /* allow up 2 channels to be used, 0 and 1 */,
			0 /* 56K modem with 56 Kbps downstream bandwidth */,
			0 /* 56K modem with 14 Kbps upstream bandwidth */);

	if (_host == NULL)
		std::cout << "An error occurred while trying to create an ENet client host.\n";
	else
		std::cout << "Succesfully created ENet client host.\n";

	enet_address_set_host(&_address, ipAdress);
	_address.port = _port;

	_peer = enet_host_connect(_host, &_address, 2, 0);

	if (_peer == NULL)
		std::cout << "No available peers for initiating an ENet connection.\n";

	// If connect send packages
	if (enet_host_service(_host, &_event, 1000) > 0 && _event.type == ENET_EVENT_TYPE_CONNECT)
	{
		_isConnected = true;
		printf("Connection to %s:%i succeeded.\n", ipAdress, _address.port);
		StartThreads();	
	}
	else
	{
		enet_peer_reset(_peer);
		printf("Connection to %s:%i failed.\n", ipAdress, _address.port);

	}
}

void Network::InitializeServer()
{
	std::cout << "Initializing server at port " << _port << ".\n";
	_address.host = ENET_HOST_ANY;
	_address.port = _port;

	_host = enet_host_create(&_address, 32, 2, 0, 0);

	if (_host == NULL)
	{
		std::cout << "An error occurred while trying to create an ENet server host.\n";
		StopThreads();
	}
	else
	{
		std::cout << "Succesfully creatinga ENet server host; server now running.\n";
		_isServer = true;
		_isConnected = true;
		StartThreads();
	}	
}

void Network::SendPacket(NetworkPacket packet, const bool reliable)
{
	if(_isConnected)
	{	
		packet.reliable = reliable; 
		_packetsToSend.push_front(packet);
	}
}

void Network::SendServerPacket(NetworkPacket packet, const bool reliable)
{
	if(_isConnected && _isServer)
	{	
		packet.reliable = reliable; 
		_serverPacketsToSend.push_front(packet);
	}
}

void Network::AddListener(PacketType packetType, INetworkListener* listener)
{
	_listeners[packetType]->push_back(listener);
}

void Network::RemoveListener(INetworkListener* listener)
{
	for (int i = 0; i < PacketType::LAST_TYPE; i++)
		_listeners[i]->remove(listener);
}

void Network::RemoveListener(PacketType packetType, INetworkListener* listener)
{
	_listeners[packetType]->remove(listener);
}

void Network::PacketSender()
{
	while(true)
	{
		std::cout << "send thread\n";
		std::list<NetworkPacket> packets = Network::GetInstance()->_packetsToSend;

		if(Network::GetInstance()->IsConnected() && packets.size() <= 0)
		{	
			continue;
		}
		else
		{
			std::list<NetworkPacket>::const_iterator iterator;

			for (iterator = packets.begin(); iterator != packets.end(); ++iterator)
			{
				NetworkPacket packet = (*iterator);
		
				ENetPacket* enetPacket = enet_packet_create(packet.GetBytes(), packet.GetSize(), packet.reliable);
				enet_peer_send(Network::GetInstance()->_peer, 0, enetPacket);
			}

			//enet_host_flush(Network::GetInstance()->_host);
			
			Network::GetInstance()->_packetsToSend.clear();
		}
	}

	std::cout << "send thread end\n";
}

void Network::PacketReciever()
{
	while (true)
	{
		enet_host_service (Network::GetInstance()->_host, & Network::GetInstance()->_event, 0);

		switch (Network::GetInstance()->_event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				printf ("A new client connected from %x:%u.\n", 
						Network::GetInstance()->_event.peer -> address.host,
						Network::GetInstance()->_event.peer -> address.port);
				/* Store any relevant client information here. */
				Network::GetInstance()->_event.peer -> data = "Client information";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
						Network::GetInstance()->_event.packet -> dataLength,
						Network::GetInstance()->_event.packet -> data,
						Network::GetInstance()->_event.peer -> data,
						Network::GetInstance()->_event.channelID);
				// Distribute the package allong the listners
				Network::GetInstance()->DistributePacket(NetworkPacket(Network::GetInstance()->_event.packet));
				/* Clean up the packet now that we're done using it. */
				enet_packet_destroy (Network::GetInstance()->_event.packet);
				break;
       
			case ENET_EVENT_TYPE_DISCONNECT:
				printf ("%s disconected.\n", Network::GetInstance()->_event.peer -> data);
				/* Reset the peer's client information. */
				Network::GetInstance()->_event.peer -> data = NULL;
		}
	}
}

void Network::DistributePacket(NetworkPacket networkPacket)
{
	int type = networkPacket.GetPacketType();
	if (type >= 0 && type < PacketType :: LAST_TYPE)
	{
		std::list<INetworkListener*>::const_iterator iterator;
		for (iterator = _listeners[type]->begin(); iterator != _listeners[type]->end(); ++iterator)
			(*iterator)->HandleNetworkMessage(networkPacket);
	}
	else
		printf("Unknown PacketType '%s' received", type);
}

bool Network::IsConnected()
{
	return _isConnected;
}

bool Network::IsServer()
{
	return _isServer;
}