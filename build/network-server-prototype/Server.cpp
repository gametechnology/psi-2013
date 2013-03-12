// Network
#include "stdafx.h"
#include <enet/enet.h>

int main(int argc, char **argv)
{
	ENetAddress address;
	ENetHost *server;
	ENetEvent event;
	ENetPacket *packet;
	
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
        return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	address.host = ENET_HOST_ANY;
	address.port = 1234;

	server = enet_host_create (&address, 32, 2, 0, 0);

	if (server == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	while(true)
	{
		while(enet_host_service(server, &event, 1000) > 0)
		{
			switch(event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
				event.peer -> data = "Client";
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

	enet_host_destroy(server);
}