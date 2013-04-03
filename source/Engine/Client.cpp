#include "Engine\Client.h"
#include <iostream>

Client::Client()
{
	printf("Creating Client.\n");
	connected = false;
	if (enet_initialize() != 0)
	{
		fprintf (stderr, "An error occurred while initializing ENet.\n");
		getchar();
	}
	atexit(enet_deinitialize);
}

Client::~Client()
{
	delete &address;
	delete &client;
	delete &event;
	delete &packet;
	delete &peer;
	delete &connected;
	enet_host_destroy(client);
}

void Client::setupClient(const char* address_name)
{
	client = enet_host_create (NULL, 1, 2, 57600 / 8, 14400 / 8);

	if (client == NULL)
	{
		fprintf(stderr, "An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
	}

	enet_address_set_host(&address, address_name);
	address.port = 1234;

	peer = enet_host_connect(client, &address, 2, 0);

	if (peer == NULL)
	{
		fprintf(stderr, "No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}

	// If connect send packages
	if (enet_host_service(client, &event, 1000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		connected = true;
		printf("Connection to %s:%i succeeded.", address_name, address.port);
		sendPacket("Client connected");
	}
	else
	{
		enet_peer_reset(peer);
		printf("Connection to %s:%i failed.", address_name, address.port);
	}
}

void Client::sendPacket(const char* data)
{
	if (connected)
	{
		packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, packet);
	}
	if(enet_host_service(client, &event, 1000) > 0)
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
			exit(EXIT_FAILURE);
		}
	}
}