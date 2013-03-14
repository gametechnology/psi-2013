#include "NetworkBoy.h"
#include <iostream>

enum PACKET_TYPE : unsigned short
{
	CLIENT_HANDSHAKE,
	SERVER_CONNECTION_ACCEPT
};

NetworkBoy::NetworkBoy()
{	
	enet_initialize();
	port = 56000;
	host = NULL;
}

NetworkBoy::~NetworkBoy()
{
	enet_deinitialize();
}

void NetworkBoy::connect(const char* ipString)
{
	std::cout << "Try connecting to server with ip: " << ipString << "\n";

	host = enet_host_create(NULL, 1, 2, 0, 0);

	if(host == NULL)
		std::cout << "Error while creating ENet client host\n";
	else
		std::cout << "Created ENet client host\n";

	enet_address_set_host(&serverAddress, ipString);
	serverAddress.port = 51234;
	serverPeer = enet_host_connect(host, &serverAddress, 2, 0);

	if(serverPeer == NULL)
		std::cout << "Error creating peer\n";
	else
		std::cout << "Created peer with server\n";
	
}

void NetworkBoy::flush()
{
	
}

void NetworkBoy::receivePackets()
{
	if(host == NULL)
		return;

	ENetEvent event;
	/* Wait up to 1000 milliseconds for an event. */
	while (enet_host_service (host, & event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf ("A new client connected from %x:%u.\n", 
					event.peer -> address.host,
					event.peer -> address.port);
			/* Store any relevant client information here. */
			event.peer -> data = "Client information";
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf ("A packet of length %u containing %s was received from %s on channel %u.\n",
					event.packet -> dataLength,
					event.packet -> data,
					event.peer -> data,
					event.channelID);
			/* Clean up the packet now that we're done using it. */
			enet_packet_destroy (event.packet);
        
			break;
       
		case ENET_EVENT_TYPE_DISCONNECT:
			printf ("%s disconected.\n", event.peer -> data);
			/* Reset the peer's client information. */
			event.peer -> data = NULL;
		}
	}
}