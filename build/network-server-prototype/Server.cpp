// Network
#include <enet/enet.h>
#include <stdio.h>
#include <list>
#include "../source/Networking_Prototype/Server/ClientInfo.h"

int main(int argc, char **argv)
{
	// The host address.
	ENetAddress address;

	// The server that will be receiving packets.
	ENetHost *server;
	
	// Received data from which packet data will be extracted.
	ENetEvent event;

	// Packet that will be send as a respond to the connected client.
	ENetPacket *packet;
	
	//We keep track of connected clients
	std::list<ClientInfo> connectedClients;
	ClientInfo newClient;

	/*
	*
	* Initializing the server. 
	*
	*/
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
        return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);


	/*
	*
	* Creating the actual server.
	*
	*/
	address.host = ENET_HOST_ANY;
	address.port = 1234;

	server = enet_host_create (&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		getchar();
		exit(EXIT_FAILURE);
	}


	//Engine startup and loop
	printf("The server has been started.");
	while(true)
	{
		while(enet_host_service(server, &event, 1000) > 0)
		{
			switch(event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
				event.peer -> data = "Client";

				//Create a new client
				newClient = ClientInfo(event.peer -> address.host, event.peer -> address.port, event.peer);
				connectedClients.push_back(newClient);

				//Send package back to peer to notify that he has entered the server						
				packet = enet_packet_create("Welcome to the STELLA INCOGNITA server!", strlen("Welcome to the STELLA INCOGNITA server!") + 1, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(event.peer, 0, packet);

				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet containing \"%s\" was received from %s on channel %u.\n", event.packet -> data, event.peer -> data, event.channelID);
				packet = enet_packet_create("Hello", strlen("Hello") + 1, ENET_PACKET_FLAG_RELIABLE);
				enet_peer_send(event.peer, 0, packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				printf("%s disconected.\n", event.peer -> data);
				event.peer -> data = NULL;
				break;
			default:
				printf("Hello!\n");
			}
		}
	}	 

	/*
	* Destroy the server.
	*/
	enet_host_destroy(server);
}