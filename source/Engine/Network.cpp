#include "Engine\Network.h"
#include "Engine\NetworkPacket.h"
#include "Engine\INetworkListener.h"
#include <iostream>

bool Network::isInitialized = false;
Network* Network::instance = 0;

Network::Network() : _port(1345)
{
	_isServer = false;
	_isConnected = false;
	connectedclients = std::list<enet_uint32>();
	for (int i = 0; i < LAST_TYPE; i++)
		_listeners[i] = new std::list<INetworkListener*>();

	if (enet_initialize() != 0)
		std::cout << "An error occurred while initializing ENet.\n";

	_packetTypeChecksum = GeneratePacketTypesChecksum();
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
	_receiverThread = new sf::Thread(&Network::PacketReciever, this);
	_receiverThread->launch();
}

void Network::StopThreads()
{
	
}

void Network::InitializeClient(const char* ipAdress, const unsigned int maxDownstream, const unsigned int maxUpstream)
{
	std::cout << "Initializing client at port " << _port << ".\n";

	_host = enet_host_create (NULL, 1, 2, maxDownstream, maxUpstream);

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

void Network::InitializeServer(size_t maxPlayers)
{
	std::cout << "Initializing server at port " << _port << ".\n";
	_address.host = ENET_HOST_ANY;
	_address.port = _port;

	_host = enet_host_create(&_address, maxPlayers, 2, 0, 0);

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
		ENetPacket* enetPacket = enet_packet_create(packet.GetBytes(), packet.GetSize(), reliable);

		if(!_isServer)
			enet_peer_send(_peer, 0, enetPacket);
		else
			_receivedPackets.push_back(NetworkPacket(enetPacket));
	}
}

void Network::SendServerPacket(NetworkPacket packet, const bool reliable)
{
	if(_isConnected && _isServer)
	{	
		ENetPacket* enetPacket = enet_packet_create(packet.GetBytes(), packet.GetSize(), reliable);

		enet_host_broadcast(_host, 0, enetPacket);
	}
}

void Network::AddListener(PacketType packetType, INetworkListener* listener)
{
	_listeners[packetType]->push_back(listener);
}

void Network::RemoveListener(INetworkListener* listener)
{
	for (int i = 0; i < LAST_TYPE; i++)
		_listeners[i]->remove(listener);
}

void Network::RemoveListener(PacketType packetType, INetworkListener* listener)
{
	_listeners[packetType]->remove(listener);
}

void Network::PacketReciever()
{
	while (true)
	{
		_mutex.lock();

		enet_host_service (Network::GetInstance()->_host, & Network::GetInstance()->_event, 0);

		switch (Network::GetInstance()->_event.type)
		{
			case ENET_EVENT_TYPE_CONNECT:
				printf ("A new client connected from %x:%u.\n", 
						Network::GetInstance()->_event.peer -> address.host,
						Network::GetInstance()->_event.peer -> address.port);
				
				// Store any relevant client information here.
				connectedclients.push_back(Network::GetInstance()->_event.peer -> address.host);
				Network::GetInstance()->_event.peer -> data = "Client information";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
						Network::GetInstance()->_event.packet -> dataLength,
						Network::GetInstance()->_event.packet -> data,
						Network::GetInstance()->_event.peer -> data,
						Network::GetInstance()->_event.channelID);

				// Add to our list of received packets
				_receivedPackets.push_back(NetworkPacket(_event.packet));

				// Clean up the packet now that we're done using it
				enet_packet_destroy (_event.packet);
				break;
       
			case ENET_EVENT_TYPE_DISCONNECT:
				printf ("%s disconected.\n", _event.peer -> data);
				// Reset the peer's client information.
				Network::GetInstance()->_event.peer -> data = NULL;
		}

		_mutex.unlock();
	}
}

void Network::DistributePacket(NetworkPacket networkPacket)
{
	int type = networkPacket.GetType();
	if (type >= 0 && type < LAST_TYPE)
	{
		std::list<INetworkListener*>::const_iterator iterator;
		for (iterator = _listeners[type]->begin(); iterator != _listeners[type]->end(); ++iterator)
			(*iterator)->HandleNetworkMessage(networkPacket);
	}
	else
		printf("Unknown PacketType '%s' received", type);
}

void Network::DistributeReceivedPackets()
{
	_mutex.lock();

	std::vector<NetworkPacket>::const_iterator iterator;
	for (iterator = _receivedPackets.begin(); iterator != _receivedPackets.end(); ++iterator)
		this->DistributePacket(*iterator);

	_mutex.unlock();
}

unsigned int Network::GeneratePacketTypesChecksum()
{
	int checksum = 0;

	for(int i = 0; i < LAST_TYPE; i++)
	{
		char* name = getPacketTypeName((PacketType)i);
		int length = strlen(name);
		
		for(int j = 0; j < length; j++)
		{
			checksum += name[j];
		}
	}

	return checksum;
}

unsigned int Network::GetPacketTypeChecksum()
{
	return _packetTypeChecksum;
}

bool Network::IsConnected()
{
	return _isConnected;
}

bool Network::IsServer()
{
	return _isServer;
}
