#include "stdafx.h"
#include <enet/enet.h>

int main(int argc, char **argv)
{
	ENetAddress address;
	ENetHost *client;
	ENetEvent event;
	ENetPacket *packet;
	ENetPeer *peer;
	bool connected = false;

	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
        return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);

	client = enet_host_create (NULL, 1, 2, 57600 / 8, 14400 / 8);

	if (client == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		getchar();
		exit(EXIT_FAILURE);
	}

	// If connect send packages
	if (enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		connected = true;
		puts("Connection to localhost:1234 succeeded.");
		packet = enet_packet_create("Hello", strlen("Hello") + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
	}
	else
	{
		enet_peer_reset(peer);
		puts("Connection to localhost:1234 failed.");
		getchar();
		exit(EXIT_FAILURE);
	}

	while(true)
	{
		while(enet_host_service(client, &event, 1000) > 0)
		{
			switch(event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				printf("connected");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				printf("A packet containing \"%s\" was received from Host on channel %u.\n", event.packet -> data, event.channelID);
				enet_packet_destroy(event.packet);
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				connected = false;
				printf("You have been disconnected.\n");
				getchar();
				exit(EXIT_FAILURE);
			}
		}
		if (connected)
		{
			packet = enet_packet_create("DATA", strlen("DATA") + 1, ENET_PACKET_FLAG_RELIABLE);
			enet_peer_send(peer, 0, packet);
		}
	}
	enet_host_destroy(client);
}